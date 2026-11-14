# Gold Premium original — compatibilidad con Windows 10/11

Este repositorio investiga y prueba una ruta de compatibilidad para conservar
la aplicación Visual Basic 6 original sin modificar Gold.exe ni sus datos de
producción.

## Estado actual

- La evidencia histórica identifica el CLSID
  `{22D6F312-B0F6-11D0-94AB-0080C74C7E95}`, el LIBID versión 1.0, las
  interfaces duales `IMediaPlayer`/`IMediaPlayer2` y los 22 eventos de
  `_MediaPlayerEvents`. Las fuentes y sus límites están en
  [`docs/06-EVIDENCIA-TYPELIB.md`](docs/06-EVIDENCIA-TYPELIB.md).
- Se inició un proyecto ATL ActiveX x86 con un backend DirectShow por
  instancia y pruebas de contrato COM/reproducción. El nuevo código aún no se
  ha compilado ni ejecutado en esta rama.
- 166 miembros del contrato estándar están declarados con sus firmas, pero
  devuelven `E_NOTIMPL`. El proyecto no es aún un reemplazo compatible y no
  debe integrarse con Gold.
- `ATLToolchainProbe.dll` es solo un diagnóstico del compilador ATL; no es un
  reproductor y no debe instalarse con Gold Premium.
- El usuario confirmó que existe el paquete fuente diagnóstico V12, pero no
  está materializado en los archivos accesibles de esta sesión. No se mezcla
  ese diagnóstico con el ActiveX de producción.

## Compilación y pruebas

`.github/workflows/build-x86.yml` conserva el probe y añade la compilación
MIDL/ATL Win32 y pruebas automatizadas en `windows-2022`, usando un MP3
sintético. Una ejecución correcta no demuestra compatibilidad con Windows
10/11 ni con el anfitrión VB6/Gold Premium. El binario del control no se
publicará como entrega de producción hasta que los miembros pendientes y la
integración estén verificados.

La ejecución histórica
[43555052228](https://github.com/urbinanavarromanfredo-sketch/gold-premium-original-compat/actions/runs/43555052228)
verificó únicamente el probe ATL x86; no compila el ActiveX nuevo.

## Seguridad

No añadir Gold.exe, Gold.INI, DBMusica.mdb, música ni datos de producción.
No modificar `C:\GOLD` ni `C:\Musica`, ni registrar globalmente el CLSID
original. Véanse
[`docs/05-SEGURIDAD-DE-ARCHIVOS.md`](docs/05-SEGURIDAD-DE-ARCHIVOS.md) y
[`docs/03-INTERFACES-OLE-Y-FALTANTES.md`](docs/03-INTERFACES-OLE-Y-FALTANTES.md).
