#!/usr/bin/env python3
"""Read-only inventory and reference search for a user-selected VB6 source tree.

The scanner never writes under the source tree unless the user explicitly sets
--output there. It does not follow directory symlinks or execute inspected files.
Binary resources are inventoried and hashed, not searched for text.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
from pathlib import Path

INVENTORY_EXTENSIONS = {".frm", ".frx", ".bas", ".cls", ".vbp", ".ocx", ".dll"}
TEXT_EXTENSIONS = {
    ".frm", ".bas", ".cls", ".vbp", ".ctl", ".pag", ".dsr", ".dob",
    ".vbg", ".txt", ".md", ".log", ".idl", ".json",
}
TERMS = (
    "frmPlayer", "frmAuto_A", "frmAuto_B", "frmAuto_C", "frmAuto_D",
    "tmPlay", "Play_Gold", "PlaySello", "PlaySelloA", "EndOfStream",
    "PlayStateChange",
)
CHUNK_SIZE = 1024 * 1024


def sha256_file(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        while chunk := stream.read(CHUNK_SIZE):
            digest.update(chunk)
    return digest.hexdigest()


def iter_files(root: Path, errors: list[dict]):
    for current, dirs, names in os.walk(root, followlinks=False):
        dirs[:] = sorted(d for d in dirs if not (Path(current) / d).is_symlink())
        for name in sorted(names):
            path = Path(current) / name
            try:
                if path.is_symlink() or not path.is_file():
                    continue
                yield path
            except OSError as exc:
                errors.append({"path": str(path), "error": str(exc)})


def scan(root: Path) -> dict:
    root = root.resolve(strict=True)
    if not root.is_dir():
        raise ValueError(f"Source path is not a directory: {root}")

    errors: list[dict] = []
    inventory = []
    references = []
    terms = {term.casefold(): term for term in TERMS}

    for path in iter_files(root, errors):
        relative = path.relative_to(root).as_posix()
        suffix = path.suffix.casefold()
        is_gold_exe = path.name.casefold() == "gold.exe"
        if suffix in INVENTORY_EXTENSIONS or is_gold_exe:
            try:
                info = {"path": relative, "kind": "Gold.exe" if is_gold_exe else suffix[1:],
                        "size_bytes": path.stat().st_size, "sha256": sha256_file(path)}
                inventory.append(info)
            except OSError as exc:
                errors.append({"path": relative, "error": str(exc)})

        if suffix not in TEXT_EXTENSIONS:
            continue
        try:
            # Decode text without altering source; malformed bytes are replaced only in the report.
            with path.open("r", encoding="utf-8-sig", errors="replace") as stream:
                for line_number, line in enumerate(stream, start=1):
                    folded = line.casefold()
                    matches = [original for key, original in terms.items() if key in folded]
                    if matches:
                        references.append({"path": relative, "line": line_number,
                                           "terms": matches, "text": line.rstrip("\r\n")[:1000]})
        except OSError as exc:
            errors.append({"path": relative, "error": str(exc)})

    inventory.sort(key=lambda item: item["path"].casefold())
    references.sort(key=lambda item: (item["path"].casefold(), item["line"]))
    return {
        "format": "gold-premium-vb6-source-inventory-v1",
        "source_root": str(root),
        "read_only": True,
        "inventory": inventory,
        "references": references,
        "errors": errors,
        "missing_named_forms": [name for name in
            ("frmPlayer.frm", "frmAuto_A.frm", "frmAuto_B.frm", "frmAuto_C.frm", "frmAuto_D.frm")
            if not any(item["path"].casefold().endswith("/" + name.casefold()) or
                       item["path"].casefold() == name.casefold() for item in inventory)],
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source", type=Path, help="Folder to scan; files are not modified")
    parser.add_argument("--output", type=Path, help="JSON report path (default: stdout)")
    args = parser.parse_args()
    try:
        report = scan(args.source)
        rendered = json.dumps(report, ensure_ascii=False, indent=2) + "\n"
        if args.output:
            args.output.write_text(rendered, encoding="utf-8")
            print(f"Report written: {args.output}")
        else:
            print(rendered, end="")
        return 0
    except (OSError, ValueError) as exc:
        parser.error(str(exc))
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
