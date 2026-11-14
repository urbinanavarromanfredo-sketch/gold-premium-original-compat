# Evidencia del Type Library de MSDXM.OCX

## Hallazgos

Dos imports públicos e independientes del Type Library histórico coinciden
en sus identificadores:

- LIBID `{22D6F304-B0F6-11D0-94AB-0080C74C7E95}`, versión 1.0.
- CLSID `MediaPlayer` `{22D6F312-B0F6-11D0-94AB-0080C74C7E95}`.
- `IMediaPlayer` IID `{22D6F311-B0F6-11D0-94AB-0080C74C7E95}`.
- `IMediaPlayer2` IID `{20D4F5E0-5475-11D2-9774-0000F80855E6}`.
- `_MediaPlayerEvents` IID `{2D3A4C40-E711-11D0-94AB-0080C74C7E95}`.

Los imports identifican `IMediaPlayer` y `IMediaPlayer2` como interfaces duales
`oleautomation` y `dispatchable`; `IMediaPlayer2` hereda de `IMediaPlayer`.
Por tanto, el tipo de la interfaz es `TKIND_INTERFACE` con `TYPEFLAG_FDUAL`,
no `TKIND_DISPATCH`. El event source sí es una dispinterface
(`TKIND_DISPATCH`).

El Type Library import enumera 178 métodos en `IMediaPlayer`, 7 métodos
añadidos por `IMediaPlayer2`, y 22 métodos en `_MediaPlayerEvents`. El valor
192 reportado anteriormente se reconcilia con los 185 métodos de ambas
interfaces y los 7 slots de `IUnknown`/`IDispatch`; no es el número de
métodos declarados directamente por `IMediaPlayer2`.

El contrato Automation de interés incluye las firmas exactas para los
miembros conocidos:

| Miembro | Firma Automation |
|---|---|
| `FileName` (1026) | `BSTR` get/put |
| `Duration` (1003) | `DOUBLE` get |
| `CurrentPosition` (1027) | `DOUBLE` get/put |
| `PlayState` (1068) | `MPPlayStateConstants` get |
| `SendPlayStateChangeEvents` (1069) | `VARIANT_BOOL` get/put |
| `SendOpenStateChangeEvents` (1062) | `VARIANT_BOOL` get/put |
| `Volume` (19), `Balance` (20) | `LONG` get/put |
| `Play` (2001), `Pause` (2002), `Stop` (2003) | sin parámetros, sin retorno Automation |
| `Open` (2010) | `BSTR` de entrada, sin retorno Automation |

Los 22 eventos, sus DISPIDs y tipos de parámetros están detallados en
[`GoldPremium.COM.Contract.json`](../contracts/GoldPremium.COM.Contract.json).
En particular, `EndOfStream` lleva `Result: LONG`, `OpenStateChange` lleva
`OldState` y `NewState` de tipo `LONG`, y `PlayStateChange` tiene la misma
firma de dos parámetros.

## Fuentes y nivel de certeza

1. [Import C++ `msdxm.tlh`](https://github.com/cwi-dis/grins/blob/7ac661912dd77d474cf3deba522d815fb906efcc/mm/win32/wmsdk/wmpsdk/include/msdxm.tlh):
   el encabezado indica que fue generado por Microsoft C/C++ desde
   `C:\winnt\system32\msdxm.ocx` (20 de marzo de 2000) y declara las interfaces
   duales y sus firmas C++.
2. [Import Delphi `MediaPlayer_TLB.pas`](https://github.com/coderserdar/DelphiComponents/blob/a6771efe25cf3c8ba308fac8a005907eb45c30e8/Embarcadero%20Code%20Central/ATViewer/Source/MediaPlayer_TLB.pas):
   el encabezado identifica `C:\WINDOWS\SYSTEM\MSDXM.OCX (1)`, LIBID versión
   1.0, flags `Dual OleAutomation Dispatchable`, DISPIDs y tipos.
3. [IDL de `_MediaPlayerEvents`](https://github.com/tongzx/nt5src/blob/daad8a087a4e75422ec96b7911f1df4669989611/Source/XPSP1/NT/inetcore/mshtml/src/time/idl/mediaprivate.idl):
   define el IID, los DISPIDs y los parámetros del origen de eventos.

Son espejos públicos de artefactos generados a partir de Type Libraries
históricos, no una copia del binario Type Library del equipo de Gold Premium.
Se han cotejado LIBID, CLSID e IIDs, pero no se ha comparado byte por byte
contra el binario instalado en el Windows XP original. Esta evidencia permite
dejar de inventar firmas del contrato estándar; no demuestra la persistencia
del formulario ni qué miembros Gold usa.

## Qué falta para integración

- `GoldPremium_COM_V12_Tres_Reproductores.zip` no está en el repositorio ni
  entre los artefactos de Actions disponibles.
- No están los datos `.frm/.frx` persistidos de los tres controles ni el mapa
  de llamadas/p-code de Gold.
- No hay un Gold de prueba autorizado y aislado ni medios de prueba adjuntos
  con los que verificar el avance automático en el anfitrión VB6.
- El repositorio de GitHub es público. No subir aquí el ejecutable original,
  datos de producción, música o materiales con derechos sin una ubicación
  privada y autorización de distribución.
