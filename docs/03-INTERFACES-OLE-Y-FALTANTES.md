# Interfaces OLE/COM necesarias y elementos pendientes

## Interfaces que debe cubrir un ActiveX alojable por VB6

Además de `IDispatch`/`IMediaPlayer2` y el punto de conexión de eventos, el reemplazo debe considerar al menos:

- `IUnknown` e `IDispatch` con type information consistente con `TKIND_DISPATCH`.
- `IOleObject`, `IOleControl`, `IOleInPlaceObject`, `IOleInPlaceActiveObject` y `IViewObject`/`IViewObject2`/`IViewObjectEx` según el modo de alojamiento usado.
- `IPersistStreamInit`, `IPersistStorage` y `IPersistPropertyBag`; no asumir que VB6 usa una única estrategia de persistencia sin inspeccionar los datos guardados.
- `IQuickActivate`, `IConnectionPointContainer`, `IProvideClassInfo` e `IProvideClassInfo2` para descubrimiento de eventos y metadatos por el contenedor.
- Los puntos de conexión adicionales observados, si el contenedor o el EXE realmente los requiere.

ATL aporta clases base para implementar el marco OLE, pero su presencia no convierte por sí sola una DLL COM normal en un control compatible. La clase final debe probarse dentro del contenedor de controles de VB6 con la persistencia real de `frmPlayer`.

## Información aún necesaria

1. Firma exacta de las 192 entradas de `IMediaPlayer2`: `FUNCDESC`, `TYPEDESC`, `ELEMDESC`, retorno, parámetros y flags.
2. Type library exacta (o volcado de alta fidelidad) y versión real del typelib `{22D6F304-B0F6-11D0-94AB-0080C74C7E95}`.
3. Bytes/estructura de persistencia del control incrustado en `frmPlayer` y propiedades serializadas de sus tres instancias.
4. Mapa real de uso de cada control (`MpSello`, `MP`, `MP`) y qué llamadas hace el programa antes, durante y al terminar una pista.
5. Código o P-code recuperable de `frmPlayer` y de los procedimientos que coordinan `tmPlay`, `Play_Gold`, `PlaySello` y `PlaySelloA`.
6. Semántica de estados y secuencia de eventos esperada por Gold, para no emitir un `EndOfStream` prematuro ni duplicado.
7. Prueba de integración Windows 10/11 con una copia aislada de Gold y archivos de audio sintéticos/de prueba.

## No inferir

- No asignar roles de música, comerciales o sellos solamente por el nombre de los controles.
- No suponer que `EndOfStream` basta para avanzar la automatización.
- No asumir que un objeto que responde a `CoCreateInstance` puede ser hospedado por VB6.
- No reemplazar globalmente el CLSID del sistema.
