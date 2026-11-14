# Contrato COM identificado

Datos tomados del informe `GOLD PREMIUM - INSPECCION COM V4: INTERFACES Y EVENTOS WMP 6.4`.

| Elemento | Valor confirmado |
|---|---|
| CLSID del control | `{22D6F312-B0F6-11D0-94AB-0080C74C7E95}` |
| Type library ID reportado | `{22D6F304-B0F6-11D0-94AB-0080C74C7E95}` |
| Interfaz predeterminada | `IMediaPlayer2` |
| IID de interfaz | `{20D4F5E0-5475-11D2-9774-0000F80855E6}` |
| Kind | `TKIND_DISPATCH` (no asumir interfaz dual) |
| Miembros informados | 192 |
| Event source | `_MediaPlayerEvents` |
| IID de eventos | `{2D3A4C40-E711-11D0-94AB-0080C74C7E95}` |
| Miembros del event source | 20 |

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
| `EndOfStream` | 3002 | `Result` |
| `OpenStateChange` | 3011 | `OldState`, `NewState` |
| `PlayStateChange` | 3012 | `OldState`, `NewState` |
| `Buffering` | 3003 | `Start` |
| `Error` | 3010 | sin parámetros informados |
| `ReadyStateChange` | -609 | `ReadyState` |

## Límite del inventario

El informe disponible registra GUID, kind, nombres, DISPIDs, tipo de invocación y nombres de parámetros. **No registra los `TYPEDESC` completos, tipos de retorno, atributos `PARAMFLAG`, valores opcionales ni la descripción íntegra de cada `FUNCDESC`.** Por tanto, no es responsable generar aún un IDL con los 192 miembros suponiendo tipos.

El contrato completo debe reproducirse desde el type information original o desde un volcado ampliado y verificable. Los DISPIDs anteriores sí sirven como base para el subconjunto de reproducción, una vez que el uso real del EXE quede correlacionado.
