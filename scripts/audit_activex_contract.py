#!/usr/bin/env python3
"""Create a conservative inventory of IMediaPlayer and IMediaPlayer2 members.

This is a source audit, not a COM conformance test: an implementation without
E_NOTIMPL still needs behavioral tests against the original control/client.
"""
from __future__ import annotations

import argparse
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
IDL = ROOT / "src/GoldPremiumMediaControl/GoldPremiumMediaControl.idl"
SOURCES = [
    ROOT / "src/GoldPremiumMediaControl/GoldPremiumMediaControl.cpp",
    ROOT / "src/GoldPremiumMediaControl/GoldPremiumMediaControl.h",
    ROOT / "src/GoldPremiumMediaControl/GoldPremiumMediaControlStubs.inc",
]
INTERFACES = ("IMediaPlayer", "IMediaPlayer2")


def interface_members(text: str):
    for interface in INTERFACES:
        match = re.search(
            rf"\binterface\s+{interface}\s*:[^{{]+\{{(.*?)^\s*\}};",
            text,
            re.DOTALL | re.MULTILINE,
        )
        if not match:
            raise RuntimeError(f"Could not find interface {interface} in {IDL}")
        for line in match.group(1).splitlines():
            line = line.strip()
            member = re.match(r"\[([^]]+)\]\s*HRESULT\s+(.+);$", line)
            if not member:
                continue
            attributes, declaration = member.groups()
            name_match = re.match(r"([A-Za-z_][A-Za-z0-9_]*)\s*\(", declaration)
            if not name_match:
                continue
            dispid_match = re.search(r"\bid\s*\(\s*(-?\d+)\s*\)", attributes)
            if not dispid_match:
                continue
            yield {
                "interface": interface,
                "dispid": dispid_match.group(1),
                "name": name_match.group(1),
                "attributes": attributes,
                "declaration": declaration,
            }


def implementation_bodies():
    bodies = {}
    function = re.compile(
        r"\bHRESULT\s+(?:(?:STDMETHODCALLTYPE)\s+)?"
        r"(?:(?:CMediaPlayer)::)?([A-Za-z_][A-Za-z0-9_]*)\s*"
        r"\([^;]*?\)\s*(?:noexcept\s*)?\{",
        re.DOTALL,
    )
    for path in SOURCES:
        text = path.read_text(encoding="utf-8-sig")
        for match in function.finditer(text):
            depth = 1
            pos = match.end()
            start = pos
            while pos < len(text) and depth:
                if text[pos] == "{":
                    depth += 1
                elif text[pos] == "}":
                    depth -= 1
                pos += 1
            bodies.setdefault(match.group(1), []).append(text[start : pos - 1])
    return bodies


def implementation_name(member):
    name = member["name"]
    attrs = member["attributes"]
    if re.search(r"\bpropget\b", attrs):
        return "get_" + name
    if re.search(r"\bpropput\b", attrs):
        return "put_" + name
    return name


def logical_return(declaration):
    retval = re.search(r"\[([^]]*\bretval\b[^]]*)\]\s*([^,]+?)\s*\*?\s*\w+", declaration)
    if retval:
        return retval.group(2).strip()
    return "void (Automation; HRESULT is the COM call status)"


def purpose(name):
    groups = (
        ("Position", ("Position", "Duration", "Seek", "Marker", "Scan", "Selection")),
        ("Transport", ("Play", "Pause", "Stop", "Cancel", "Next", "Previous", "Entry")),
        ("Media source and metadata", ("File", "Source", "Media", "Channel", "Contact", "Creation")),
        ("Playback/audio settings", ("Volume", "Balance", "Mute", "Audio", "Rate", "Stream", "Language")),
        ("Control appearance and input", ("Show", "Display", "Video", "Caption", "Cursor", "Enabled", "Enable", "Windowless", "AutoSize")),
        ("Playback status and diagnostics", ("State", "Ready", "Error", "Warning", "Buffer", "Broadcast", "Packet", "Reception", "SoundCard", "Codec", "Connection")),
        ("DVD/media-list features", ("DVD", "Title", "Chapter", "Entry", "Parameter", "Dialog")),
    )
    for label, fragments in groups:
        if any(fragment.lower() in name.lower() for fragment in fragments):
            return label + "; exact semantics must be checked against the WMP 6.4 type library/client"
    return "Other ActiveX contract member; semantics need source/type-library verification"


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--output", type=Path, default=ROOT / "docs/07-AUDITORIA-METODOS-ACTIVEX.md")
    args = parser.parse_args()

    members = list(interface_members(IDL.read_text(encoding="utf-8-sig")))
    bodies = implementation_bodies()
    rows = []
    for member in members:
        impl = implementation_name(member)
        candidates = bodies.get(impl, [])
        if not candidates:
            status = "Sin cuerpo de implementación localizado"
        elif any("E_NOTIMPL" in body for body in candidates):
            status = "Devuelve E_NOTIMPL (pendiente)"
        else:
            status = "Sin E_NOTIMPL en el cuerpo localizado; comportamiento no validado"
        if status != "Sin E_NOTIMPL en el cuerpo localizado; comportamiento no validado":
            safe = "No implementar por inferencia: falta evidencia de uso/comportamiento del cliente original"
        else:
            safe = "Requiere prueba funcional; la ausencia de E_NOTIMPL no demuestra compatibilidad"
        rows.append((member, status, safe))

    out = [
        "# Auditoría automatizada de miembros ActiveX",
        "",
        "> Generado por `scripts/audit_activex_contract.py` desde el IDL y los cuerpos C++. Es un inventario estático, no una prueba COM ni una afirmación de compatibilidad.",
        "",
        f"Miembros enumerados: **{len(rows)}**. Pendientes explícitos E_NOTIMPL: **{sum('E_NOTIMPL' in status for _, status, _ in rows)}**. Sin cuerpo localizado: **{sum(status.startswith('Sin cuerpo') for _, status, _ in rows)}**.",
        "",
        "La columna de declaración preserva la firma y los parámetros del IDL. El tipo Automation de retorno se toma del parámetro `[retval]`, si existe; los métodos sin retval retornan `void` al cliente Automation (el HRESULT comunica el resultado COM). La etiqueta de función es una clasificación por nombre, no una afirmación de semántica verificada.",
        "",
        "| Interfaz | Miembro | DISPID | Tipo Automation de retorno | Función aproximada | Estado fuente | Implementación segura ahora |",
        "|---|---|---:|---|---|---|---|",
    ]
    for member, status, safe in rows:
        declaration = member["declaration"].replace("|", "\\|")
        out.append(
            f"| `{member['interface']}` | `{declaration}` | {member['dispid']} | `{logical_return(declaration)}` | {purpose(member['name'])} | {status} | {safe} |"
        )
    out += [
        "",
        "## Criterio de implementación",
        "",
        "No se cambia el IDL ni se sustituyen los miembros pendientes por valores ficticios. El contrato define firmas/DISPIDs, pero no prueba cuáles usa Gold ni cómo interpreta sus estados/errores. Solo se debe implementar un miembro cuando su semántica esté corroborada por el typelib original/documentación autoritativa y exista prueba automatizada con resultado esperado. El reporte se debe regenerar después de cada cambio.",
        "",
    ]
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text("\n".join(out), encoding="utf-8")
    print(f"Wrote {args.output}; members={len(rows)}; E_NOTIMPL={sum('E_NOTIMPL' in s for _, s, _ in rows)}")


if __name__ == "__main__":
    main()
