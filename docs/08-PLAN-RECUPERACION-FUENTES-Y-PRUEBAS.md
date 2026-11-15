# Source recovery and test blockers — 2026-11-15

## Scope and baseline

This work continues from branch `work/activex-compat-investigation`, reference commit `59d2277f43afc9d85b3584f224cbbc2c6742d364`. The available repository tree at that reference contains the ATL x86 ActiveX sources, its IDL, generated-method stubs, a COM/DirectShow test host, a contract JSON inventory, and CI configuration. It does not contain VB6 source forms/modules or the original MSDXM.OCX type library binary. No conclusion that depends on those missing inputs is made here.

## What the repository currently permits verifying

- Source inspection shows DirectShow events are drained using `IMediaEventEx::GetEvent`; the current handler calls `FreeEventParams` before branching on the event code and reading `parameter1`. This is a source-order defect: event parameters must be consumed before their associated resources are freed. This report records the defect; no runtime reproduction has yet been performed.
- `EC_COMPLETE` changes PlayState to stopped and raises `EndOfStream`; `EC_ERRORABORT` only changes PlayState to stopped. Open/Play failures return the failed HRESULT, but the available test host does not separately assert event ordering or error recovery.
- The current Windows Server CI test host covers COM/OLE metadata, basic persistence round-trip, three object instances with independent volume values, transport, timing, event receipt, and a client callback that reopens/plays a test file. Its log shows `VFW_E_NO_AUDIO_HARDWARE` followed by a passing software playback/event test. This is not audible-output evidence.
- The test's continuation callback uses the same fixture again; it verifies a client-issued second play, not a Gold playlist or Gold's automatic selection logic.
- `IPersistStreamInit` is tested only by saving/loading the properties configured by this host. The serialized data and property set used by Gold's VB6 designer remain unknown.

## DirectShow event-parameter fix and validation status

The identified defect is that `FreeEventParams` is called before code reads `EC_COMPLETE`'s result parameter. A safe correction must copy `eventCode` and parameters into local values before freeing the event resources, then handle the copied values. Every dequeued event must still have its event parameters freed exactly once, including unknown event types. `EC_ERRORABORT` recovery and state/event policy must not be invented without evidence.

The issue is not claimed runtime-reproduced in this environment. A Windows CI test should assert event delivery and result argument while draining the graph. That test cannot guarantee the old ordering fails deterministically because the result is a scalar, but it does guard the intended forwarding contract. Injecting `EC_ERRORABORT` requires a controlled filter/test graph or a deterministic failing media source; a missing file only tests `OpenGraph` failure, not asynchronous graph abort. Do not treat those cases as equivalent.

## Reproducible original type-library comparison

No original `MSDXM.OCX` binary was found in the repository. Therefore no IDL-versus-original comparison has been executed and the IDs in the current IDL remain evidence-based declarations, not locally verified against Gold's binary.

When the authorized original OCX is available on an isolated Windows machine:

1. Record its path, version, architecture, SHA-256, and provenance; do not register or alter it.
2. Use Visual Studio's OLE/COM Object Viewer (`oleview.exe`) to load the file directly and inspect the type library, or use a trusted read-only typelib dumper. Do not rely on the machine registry's possibly different registered OCX.
3. Export/save the typelib as IDL without changing it. Preserve raw output and tool version with the evidence.
4. Compare LIBID and version, coclass CLSID, interface IIDs/base interfaces/typekind/flags, every member's DISPID/invkind/parameter order/types/directions/retval and every event signature against `GoldPremiumMediaControl.idl`.
5. Report differences explicitly; never auto-rewrite the project IDL from a partial dump. Have a second review verify any correction.

There is no comparator against an original binary in this repository because that binary is absent. `scripts/audit_activex_contract.py` inventories the project's own declarations only; it is not an original-type-library comparator.

## Read-only VB6 source inventory tool

`tools/vb6_source_inventory.py` accepts a folder path, inventories `.frm`, `.frx`, `.bas`, `.cls`, `.vbp`, `.ocx`, `.dll`, and any `Gold.exe`, and searches text source files for the requested form/procedure/event names. Binary files are inventoried with size and SHA-256 but are not executed or searched as text. It does not follow directory symlinks or write into the source tree. Output can be JSON to stdout or to a user-selected `--output` path.

Run:

```powershell
py -3 tools/vb6_source_inventory.py 'D:\authorized\vb6-source-copy' --output '.\vb6-inventory.json'
py -3 -m unittest discover -s tests\SourceInventoryTests -v
```

The tool must only be pointed at an authorized source copy. Do not use it to modify or process production databases/media.

## Exact original inputs still required

No `.frm`, `.frx`, `.bas`, `.cls`, `.vbp`, `.ocx`, `.dll`, or `Gold.exe` source-package artifacts are present in the repository tree. Specifically request:

- `frmPlayer.frm`, plus `frmPlayer.frx` if referenced by the form.
- `frmAuto_A.frm`, `frmAuto_B.frm`, `frmAuto_C.frm`, and `frmAuto_D.frm`, plus each associated `.frx` if present.
- The original `.vbp` and every referenced `.bas` and `.cls` file, including modules implementing `tmPlay`, `Play_Gold`, `PlaySello`, `PlaySelloA`, player event handlers, and track-selection/advance calls. Their source filenames are unknown and must be obtained from the `.vbp`/source inventory, not guessed.
- A read-only copy of the exact `MSDXM.OCX` used to build the Gold project (or extracted original typelib and export procedure), including version, architecture, SHA-256, and provenance.
- A sanitized copy/export of the VB6 form's persisted OLE control data for all three instances, with production paths and personal data removed, if legally/technically available.
- For actual integration only: an authorized isolated Gold Premium test installation and synthetic audio fixtures. Do not upload production Gold.exe, INI/database, or music to this repository.

## VB6 lab host feasibility

A small VB6 host can be evaluated only after access to a licensed VB6 toolchain and a reproducible private activation arrangement for the control. VB6's designer may require type-library registration at design time; runtime manifest activation and design-time ActiveX discovery are separate concerns. Do not register this CLSID globally or replace the system Windows Media Player registration. Existing C++ test host already provides a separate x86 three-instance COM laboratory; it is not a VB6 container. This stage does not fabricate a `.vbp`/`.frm` host or assert that VB6 hosting works.

Next decision: provide the authorized source/OCX evidence, then determine whether a VB6-only host can be built with a local VB6 compiler and isolated activation. Keep it separate from Gold.exe.

## Test matrix and environment requirements

| Test | Current evidence/status | Required environment |
|---|---|---|
| ATL x86 build and COM/DirectShow software host | CI job exists; latest inspected job passed these software checks, but used no audio hardware | Windows Server CI; does not establish OS compatibility |
| DirectShow event-parameter ordering regression | Source defect identified; runtime regression test pending | Windows x86 test host; ideally controlled test graph/event source |
| Open failure and graph-abort recovery | Not separately covered; graph abort injection pending | Windows x86 test host; deterministic failing source/filter for EC_ERRORABORT |
| Audible signal, one instance | Not run | Windows 10 and Windows 11 separately, physical/default audio output and operator verification |
| Three simultaneous independent audible streams | Not established by silent CI | Windows 10 and Windows 11 with output device; isolated fixtures, per-instance position/state/event assertions |
| VB6 ActiveX creation/events/persistence | Not run | Licensed VB6 x86 environment and isolated/private activation host |
| Gold's actual three-player usage and automatic next track | Blocked by missing originals | Authorized Gold Premium test installation, original forms/modules, synthetic playlist/audio |
| Modes A/B/C/D | Unknown; no source or behavioral specification | Original mode forms/modules and isolated Gold test setup |
| Original typelib comparison | Not run; original MSDXM.OCX absent | Exact authorized OCX binary and read-only typelib inspection tool |

Windows 10 and Windows 11 results must be recorded independently. A CI/Server pass, a nonzero duration, graph clock movement, or Null Renderer is not audible-output verification.
