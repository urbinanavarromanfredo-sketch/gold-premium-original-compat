# Gold Premium original — compatibilidad con Windows 10/11

Este repositorio contiene la investigación y las pruebas para conservar la
aplicación original de Visual Basic 6 sin modificar el ejecutable ni sus datos
de producción.

## Estado comprobable

- El inventario del contrato COM confirma el CLSID
  `{22D6F312-B0F6-11D0-94AB-0080C74C7E95}`, el LIBID/version 1.0 y las
  interfaces del Media Player 6.4. La evidencia del Type Library identifica
  `IMediaPlayer2` como interfaz dual que hereda `IMediaPlayer`, y `_MediaPlayerEvents`
  como dispinterface con 22 eventos. Esto corrige datos contradictorios del
  inventario inicial; las fuentes y el alcance se explican en
  [`docs/06-EVIDENCIA-TYPELIB.md`](docs/06-EVIDENCIA-TYPELIB.md).
- El workflow de Windows Server 2022 compila un probe ATL x86 y verifica que
  sea PE32/x86. `ATLToolchainProbe.dll` **no es** un reproductor y no debe
  instalarse con Gold Premium.
- La referencia pública del Type Library da firmas y tipos exactos para las
  interfaces estándar. No están disponibles aquí el binario original para
  cotejarlo, los datos serializados de `frmPlayer`, el código/p-code de Gold ni
  evidencia de qué miembros llama el programa. No se declara ni se entrega un
  control ActiveX sustituto mientras falte la validación del anfitrión real.

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
