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

- **F0 — Toolchain:** completada anteriormente para el probe, no para el ActiveX nuevo.
- **F1 — Contrato:** el IDL inicial y los DISPIDs están en el árbol; MIDL aún debe compilarse y falta cotejo binario con el Type Library original. Las propiedades históricas del formulario siguen sin confirmar.
- **F2 — Contenedor:** el esqueleto ATL y el host de activación privada están escritos; compilación y prueba OLE real pendientes.
- **F3 — Audio/eventos:** implementados en código con un grafo DirectShow por instancia; falta ejecutar las pruebas x86 en Windows.
- **F4 — Integración aislada:** activar COM privado desde copia de Gold; verificar interfaz, botones y modos A–D.
- **F5 — Paquete de prueba:** incluir EXE original sin modificar y DLL solo cuando todas las pruebas tengan evidencia.

Las pruebas nuevas están preparadas para el workflow, no ejecutadas todavía.
166 métodos estándar devuelven `E_NOTIMPL`, por lo que la clase no debe
presentarse como reemplazo compatible. Tampoco se sabe si Gold avanza al
recibir `EndOfStream`: el test de cliente solo comprueba que un cliente pueda
iniciar la siguiente pista al recibir ese evento.

## Activación privada

El host de pruebas usa un manifiesto Side-by-Side activado en el proceso y
redirige el CLSID a una DLL local, sin registrar globalmente la clase. Esto
prueba el mecanismo en el host de prueba; no demuestra todavía la activación
en el ejecutable original de Gold ni resuelve la integración sin modificar sus
archivos.

El control carga el Type Library embebido usando el recurso 101 para que
`IDispatch` y `IProvideClassInfo2` no dependan del registro global. En Windows
Server sin hardware de audio, DirectShow se prueba con `Null Renderer`; ese
resultado solo acredita reproducción silenciosa, temporización y eventos, no
salida audible.

El diagnóstico V12 se mantendrá en un target separado. El usuario confirma
que su ZIP existe, pero el archivo no está materializado en esta sesión; no se
ha copiado ni mezclado código diagnóstico con el ActiveX.
