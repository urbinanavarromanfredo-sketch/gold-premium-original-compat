# Implementación ATL ActiveX — estado de desarrollo

Esta carpeta contiene un proyecto ATL `CComControl` x86 y el IDL derivado de
los imports históricos documentados de MSDXM.OCX 1.0. Es código en desarrollo,
**no un reemplazo terminado ni distribuible**.

## Implementado en el código fuente

- CLSID del control, LIBID, herencia dual de `IMediaPlayer2`, DISPIDs de
  Automation y declaración del origen de 22 eventos.
- Interfaces OLE/ActiveX, `IPersistStreamInit`, un grafo DirectShow por
  instancia, apertura de MP3, controles de reproducción, duración/posición,
  volumen y balance.
- Connection points por instancia para `PlayStateChange`, `OpenStateChange`
  y `EndOfStream`.
- `IDispatch` y `IProvideClassInfo2` cargan el typelib incrustado desde el
  recurso 101 de la DLL, sin depender de registro global.
- Manifiesto de activación privada para las pruebas x86. La DLL no exporta
  `DllRegisterServer` ni escribe un registro COM global.
- Si Windows informa `VFW_E_NO_AUDIO_HARDWARE`, el control usa `Null Renderer`
  para conservar reloj, posición y eventos en entornos sin dispositivo de
  audio. Ese modo es silencioso; no acredita salida audible.

## Limitaciones — no integrar todavía con Gold

- El typelib exacto no se ha cotejado con el `MSDXM.OCX` de la máquina XP
  original; la evidencia disponible son imports públicos.
- Los otros 166 métodos de `IMediaPlayer`/`IMediaPlayer2` conservan firmas
  declaradas y devuelven `E_NOTIMPL`. Tener esos slots no significa que la
  interfaz completa sea compatible.
- Se desconocen las propiedades persistidas por el formulario original y las
  llamadas que efectivamente hace Gold.exe. El mapa de persistencia actual
  contiene solo cinco propiedades.
- `OpenStateChange` usa 0 (cerrado) y 6 (abierto), valores corroborados en un
  cliente público antiguo de Windows Media Player, no en el typelib binario
  original de Gold.
- El host de pruebas cubre interfaces COM, estado, propiedades, persistencia,
  reproducción y eventos; no aloja el control en VB6 ni ejecuta Gold.
- La prueba en Windows Server usa el modo silencioso solo cuando no hay
  hardware de audio. Reproduce el MP3 y verifica temporización/eventos, pero no
  prueba sonido audible.
- El usuario confirmó que existe el archivo diagnóstico V12, pero no está
  materializado en los archivos accesibles de esta sesión. El diagnóstico
  debe integrarse en un target separado y no forma parte de esta DLL.

El workflow de GitHub compila IDL/ATL como Win32 y ejecuta las pruebas con un
MP3 sintético. Aunque pase en Windows Server, eso no verifica Windows 10/11 ni
la integración con Gold Premium. No generar instalador ni Release mientras
persistan las limitaciones anteriores.
