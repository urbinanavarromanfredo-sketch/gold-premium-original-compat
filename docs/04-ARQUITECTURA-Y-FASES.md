# Arquitectura y estado de implementación

## Límite del reemplazo

Un servidor COM en proceso (DLL) de 32 bits, construido con C++/ATL, que conserve el CLSID esperado solo dentro del contexto privado de Gold Premium. El control expone la Automation compatible y aloja un motor de reproducción encapsulado. Las tres instancias deben poseer estado, callbacks y sesión de audio independientes.

## Capas

1. **ActiveX/OLE host layer:** ciclo de vida, activación, ventana, propiedades persistentes y negociación con el contenedor VB6.
2. **Automation compatibility layer:** IID `IMediaPlayer2`, DISPIDs y tipos correctos; métodos/propiedades usados por Gold.
3. **Event connection layer:** `_MediaPlayerEvents` y DISPIDs originales, con orden/argumentos compatibles.
4. **Playback engine:** grafo DirectShow independiente por instancia; queda pendiente confirmar la disponibilidad del decodificador/renderizador en los entornos objetivo.
5. **Diagnostics/tests:** logs, tests unitarios y anfitrión de integración x86; sin rutas de producción.

## Fases de entrega

- **F0 — Toolchain:** el probe ATL y el ActiveX/host x86 compilan en Windows Server 2022.
- **F1 — Contrato:** el IDL y los DISPIDs compilan; falta cotejo binario con el Type Library original. Las propiedades históricas del formulario siguen sin confirmar.
- **F2 — Contenedor:** el host x86 crea el control por activación privada, consulta interfaces OLE/COM y prueba persistencia.
- **F3 — Audio/eventos:** pruebas x86 de MP3 sintético, tres instancias, reproducción, pausa, detención, posición, eventos y avance al siguiente archivo pasaron con Null Renderer en Windows Server 2022. No se verificó salida audible.
- **F4 — Integración aislada:** activar COM privado desde copia de Gold; verificar interfaz, botones y modos A–D.
- **F5 — Paquete de prueba:** incluir EXE original sin modificar y DLL solo cuando todas las pruebas tengan evidencia.

El run [43563582749](https://github.com/urbinanavarromanfredo-sketch/gold-premium-original-compat/actions/runs/43563582749)
ejecutó satisfactoriamente las pruebas disponibles. 166 métodos estándar
devuelven `E_NOTIMPL`, por lo que la clase no debe presentarse como reemplazo
compatible. El cliente de prueba sí inicia otro archivo al recibir
`EndOfStream`; falta comprobar el comportamiento de Gold.exe.

## Activación privada

El host de pruebas usa un manifiesto Side-by-Side activado en el proceso y
redirige el CLSID a una DLL local, sin registrar globalmente la clase. Esto
prueba el mecanismo en el host de prueba; no demuestra todavía la activación
en el ejecutable original de Gold ni resuelve la integración sin modificar sus
archivos.

El control carga el Type Library embebido usando el recurso 101 para que
`IDispatch` y `IProvideClassInfo2` no dependan del registro global. El run
actual abrió y probó MP3 sintético en Windows Server con `Null Renderer`;
acredita la ruta de decodificación, temporización y eventos, no salida audible.
Un run anterior devolvió `E_NOTIMPL` al abrir MP3 y falló también al abrir el
WAV alternativo, por lo que no acreditó reproducción.

El diagnóstico V12 se mantendrá en un target separado. El usuario confirmó
que su ZIP existe; el archivo todavía no está materializado en el checkout
actual y no se ha copiado ni mezclado código diagnóstico con el ActiveX.
