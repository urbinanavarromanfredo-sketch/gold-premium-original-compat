# Interfaces OLE/COM necesarias y elementos pendientes

## Interfaces que debe cubrir un ActiveX alojable por VB6

Además de `IDispatch`/`IMediaPlayer2` y el punto de conexión de eventos, el reemplazo debe considerar al menos:

- `IUnknown` e `IDispatch` con el type information dual de `IMediaPlayer2`
  (`TKIND_INTERFACE`, `oleautomation`, `dispatchable`).
- `IOleObject`, `IOleControl`, `IOleInPlaceObject`, `IOleInPlaceActiveObject` y `IViewObject`/`IViewObject2`/`IViewObjectEx` según el modo de alojamiento usado.
- `IPersistStreamInit`, `IPersistStorage` y `IPersistPropertyBag`; no asumir que VB6 usa una única estrategia de persistencia sin inspeccionar los datos guardados.
- `IQuickActivate`, `IConnectionPointContainer`, `IProvideClassInfo` e `IProvideClassInfo2` para descubrimiento de eventos y metadatos por el contenedor.
- Los puntos de conexión adicionales observados, si el contenedor o el EXE realmente los requiere.

ATL aporta clases base para implementar el marco OLE, pero su presencia no convierte por sí sola una DLL COM normal en un control compatible. La clase final debe probarse dentro del contenedor de controles de VB6 con la persistencia real de `frmPlayer`.

## Información aún necesaria

1. El Type Library binario exacto que utiliza el Gold Premium original para
   cotejarlo con los imports públicos de `MSDXM.OCX` 1.0.
2. Bytes/estructura de persistencia del control incrustado en `frmPlayer` y
   propiedades serializadas de sus tres instancias.
3. Mapa real de uso de cada control (`MpSello`, `MP`, `MP`) y qué llamadas hace
   el programa antes, durante y al terminar una pista.
4. Código o P-code recuperable de `frmPlayer` y de los procedimientos que
   coordinan `tmPlay`, `Play_Gold`, `PlaySello` y `PlaySelloA`.
5. Secuencia de estados/eventos esperada por Gold, para no emitir un
   `EndOfStream` prematuro ni duplicado.
6. Prueba de integración Windows 10/11 con una copia aislada y autorizada de
   Gold y archivos de audio de prueba.
7. El paquete `GoldPremium_COM_V12_Tres_Reproductores.zip`: no aparece en los
   archivos rastreados ni en los artefactos de las ejecuciones de Actions
   inspeccionadas.

## No inferir

- No asignar roles de música, comerciales o sellos solamente por el nombre de los controles.
- No suponer que `EndOfStream` basta para avanzar la automatización.
- No asumir que un objeto que responde a `CoCreateInstance` puede ser hospedado por VB6.
- No reemplazar globalmente el CLSID del sistema.

Las firmas base de las interfaces y el event source ya están descritas en
imports públicos coincidentes por LIBID/CLSID/IID; véase
[`06-EVIDENCIA-TYPELIB.md`](06-EVIDENCIA-TYPELIB.md). El bloqueo actual no es
inventar esas firmas, sino verificar el typelib usado por Gold y su
persistencia/uso real.
