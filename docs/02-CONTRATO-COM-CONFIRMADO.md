# Contrato COM identificado

El inventario V4 se ha contrastado con imports públicos del Type Library
histórico `MSDXM.OCX` 1.0 y con el IDL de eventos. Los detalles y referencias
están en [`06-EVIDENCIA-TYPELIB.md`](06-EVIDENCIA-TYPELIB.md).

| Elemento | Valor confirmado |
|---|---|
| CLSID del control | `{22D6F312-B0F6-11D0-94AB-0080C74C7E95}` |
| Type library ID reportado | `{22D6F304-B0F6-11D0-94AB-0080C74C7E95}` |
| Interfaz predeterminada | `IMediaPlayer2` |
| IID de interfaz | `{20D4F5E0-5475-11D2-9774-0000F80855E6}` |
| Kind / flags | `TKIND_INTERFACE`; dual, oleautomation, dispatchable |
| Interfaz base | `IMediaPlayer`, IID `{22D6F311-B0F6-11D0-94AB-0080C74C7E95}` |
| Miembros informados | 192 slots contando herencia y `IUnknown`/`IDispatch` |
| Event source | `_MediaPlayerEvents` |
| IID de eventos | `{2D3A4C40-E711-11D0-94AB-0080C74C7E95}` |
| Kind del event source | `TKIND_DISPATCH` |
| Miembros del event source | 22 |

## DISPIDs de miembros Automation identificados

| Nombre | DISPID | Invocación informada |
|---|---:|---|
| `FileName` | 1026 | PROPERTYGET / PROPERTYPUT |
| `Duration` | 1003 | PROPERTYGET |
| `CurrentPosition` | 1027 | PROPERTYGET / PROPERTYPUT |
| `PlayState` | 1068 | PROPERTYGET |
| `SendPlayStateChangeEvents` | 1069 | PROPERTYGET / PROPERTYPUT |
| `SendOpenStateChangeEvents` | 1062 | PROPERTYGET / PROPERTYPUT |
| `Volume` | 19 | PROPERTYGET / PROPERTYPUT |
| `Balance` | 20 | PROPERTYGET / PROPERTYPUT |
| `Play` | 2001 | FUNC |
| `Pause` | 2002 | FUNC |
| `Stop` | 2003 | FUNC |
| `Open` | 2010 | FUNC |

## Eventos de salida confirmados

| Evento | DISPID | Parámetros indicados por el informe |
|---|---:|---|
| `EndOfStream` | 3002 | `Result: LONG` |
| `OpenStateChange` | 3011 | `OldState: LONG`, `NewState: LONG` |
| `PlayStateChange` | 3012 | `OldState: LONG`, `NewState: LONG` |
| `Buffering` | 3003 | `Start: VARIANT_BOOL` |
| `Error` | 3010 | sin parámetros |
| `ReadyStateChange` | -609 | `ReadyState: ReadyStateConstants` |

El contrato JSON incluye las firmas Automation confirmadas y las 22 firmas del
event source: [`GoldPremium.COM.Contract.json`](../contracts/GoldPremium.COM.Contract.json).

## Discrepancias y alcance

El informe V4 describía `IMediaPlayer2` como `TKIND_DISPATCH` y el event
source con 20 miembros. Los imports del Type Library que comparten LIBID,
CLSID e IID muestran que `IMediaPlayer2` es dual (`TKIND_INTERFACE`) y que
`_MediaPlayerEvents` tiene 22 eventos. El conteo 192 es consistente con los
178 métodos de `IMediaPlayer`, 7 añadidos en `IMediaPlayer2` y 7 slots
`IUnknown`/`IDispatch`; no significa 192 métodos declarados directamente en
`IMediaPlayer2`.

Los imports son evidencia detallada del contrato estándar, pero el binario
Type Library del equipo XP no está en este repositorio para comparar versión,
atributos o persistencia del control. Tampoco se ha correlacionado el contrato
con las llamadas y los datos de diseño que Gold realmente guarda.
