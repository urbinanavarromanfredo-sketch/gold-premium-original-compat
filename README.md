# Gold Premium original — compatibilidad con Windows 10/11

Este repositorio contiene la investigación y las pruebas para conservar la
aplicación original de Visual Basic 6 sin modificar el ejecutable ni sus datos
de producción.

## Estado comprobable

- El inventario del contrato COM confirma el CLSID
  `{22D6F312-B0F6-11D0-94AB-0080C74C7E95}`, la interfaz dispinterface
  `IMediaPlayer2` (IID `{20D4F5E0-5475-11D2-9774-0000F80855E6}`, 192 miembros
  reportados) y el origen de eventos `_MediaPlayerEvents`.
- El workflow de Windows Server 2022 compila un probe ATL x86 y verifica que
  sea PE32/x86. `ATLToolchainProbe.dll` **no es** un reproductor y no debe
  instalarse con Gold Premium.
- El Type Library original completo, los tipos y firmas de sus 192 miembros,
  los datos serializados de los tres controles y su comportamiento en el
  contenedor VB6 todavía no están disponibles. No se declara ni se entrega un
  control ActiveX sustituto mientras falte esa evidencia.

## Compilación y registros

`.github/workflows/build-x86.yml` ejecuta la comprobación en `windows-2022`.
El artefacto `atl-toolchain-probe-x86` solo demuestra la compilación x86. Los
registros de MSBuild (texto diagnóstico y binlog) se publican por separado,
incluso si la compilación falla.

La ejecución [43555052228](https://github.com/urbinanavarromanfredo-sketch/gold-premium-original-compat/actions/runs/43555052228)
finalizó correctamente: MSBuild reportó 0 errores y 0 advertencias, y la
verificación confirmó PE x86. El resultado corresponde solo al probe, no a un
reproductor. Los registros se conservarán como artefacto de Actions durante
90 días.

## Límites de seguridad

No añadir aquí `Gold.exe`, `Gold.INI`, `DBMusica.mdb`, música ni archivos de
producción. No modificar `C:\GOLD`, `C:\Musica` ni registrar globalmente el
CLSID original de Windows Media Player. Véanse
[`docs/05-SEGURIDAD-DE-ARCHIVOS.md`](docs/05-SEGURIDAD-DE-ARCHIVOS.md) y
[`docs/03-INTERFACES-OLE-Y-FALTANTES.md`](docs/03-INTERFACES-OLE-Y-FALTANTES.md).
