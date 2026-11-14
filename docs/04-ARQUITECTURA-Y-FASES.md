# Arquitectura propuesta

## Límite del reemplazo

Un servidor COM en proceso (DLL) de 32 bits, construido con C++/ATL, que conserve el CLSID esperado solo dentro del contexto privado de Gold Premium. El control expone la Automation compatible y aloja un motor de reproducción encapsulado. Las tres instancias deben poseer estado, callbacks y sesión de audio independientes.

## Capas

1. **ActiveX/OLE host layer:** ciclo de vida, activación, ventana, propiedades persistentes y negociación con el contenedor VB6.
2. **Automation compatibility layer:** IID `IMediaPlayer2`, DISPIDs y tipos correctos; métodos/propiedades usados por Gold.
3. **Event connection layer:** `_MediaPlayerEvents` y DISPIDs originales, con orden/argumentos compatibles.
4. **Playback engine:** backend nativo Windows (la decisión final se tomará al implementar y probar audio), separado por instancia.
5. **Diagnostics/tests:** logs, tests unitarios y anfitrión de integración x86; sin rutas de producción.

## Fases de entrega

- **F0 — Toolchain:** esta primera entrega. Verifica MSVC x86 + ATL en runner Windows.
- **F1 — Contrato:** completar IDL/typeinfo y leer la persistencia auténtica del control.
- **F2 — Contenedor:** activar y persistir el control en un host OLE de prueba x86.
- **F3 — Audio/eventos:** reproducir archivos de prueba en tres instancias independientes y validar estados/eventos.
- **F4 — Integración aislada:** activar COM privado desde copia de Gold; verificar interfaz, botones y modos A–D.
- **F5 — Paquete de prueba:** incluir EXE original sin modificar y DLL solo cuando todas las pruebas tengan evidencia.

## Activación privada

El camino a evaluar es un manifiesto Side-by-Side junto al EXE, con el CLSID original redirigido a una DLL local. Microsoft documenta que los contextos de activación pueden resolver una clase COM desde el manifiesto antes de consultar el Registro. Eso evita registrar o sustituir globalmente el componente; no elimina la necesidad de comprobar el manifiesto que use el EXE y su contexto real.
