# Auditoría y validación de la siguiente etapa

## Inventario de miembros pendientes

Generar/actualizar la matriz completa (incluye nombre, interfaz, DISPID, firma, retorno Automation, clasificación funcional aproximada y estado fuente) desde el IDL y las implementaciones actuales:

```powershell
py -3 scripts/audit_activex_contract.py
```

El resultado se escribe en `docs/07-AUDITORIA-METODOS-ACTIVEX.md`. La clasificación de función es deliberadamente conservadora: el IDL garantiza tipos y DISPIDs, pero no demuestra qué miembros invoca Gold. Que un miembro ya no devuelva `E_NOTIMPL` tampoco constituye prueba funcional. No implementar accesores o métodos con resultados ficticios; comparar primero con el typelib binario exacto de MSDXM.OCX usado por Gold y realizar pruebas con el cliente real.

## Validación automatizada de audio/COM

El workflow `.github/workflows/build-x86.yml` es la ruta automatizada existente. En Windows Server 2022 valida compilación y pruebas de software, y puede seleccionar `Null Renderer` si no existe dispositivo de sonido. Un éxito en CI/Server no valida salida audible, alojamiento dentro de VB6, Gold.exe, ni Windows 10/11. El resultado previo documentado con Null Renderer fue silencioso; no se debe contar como prueba de sonido.

## Protocolo manual en Windows 10 y 11 (pendiente de ejecución)

Usar una VM o equipo de prueba aislado, con una copia autorizada del programa y medios sintéticos propios. No usar ni modificar datos de producción.

1. Registrar versión/build de Windows, arquitectura, dispositivo de salida predeterminado, controlador, nivel de volumen y SHA-256 de DLL, EXE host y fixture. Confirmar que la DLL y el proceso VB6 son x86.
2. Copiar el control y typelib en una carpeta de prueba. Activarlo mediante el manifiesto privado de la aplicación/host; no ejecutar `regsvr32` ni registrar el CLSID WMP globalmente.
3. Abrir la app de prueba en VB6 x86 (o el host de integración VB6 reproducible), insertar/controlar el ActiveX sin Gold.exe primero; verificar creación, visibilidad, propiedades, eventos y liberación. Guardar logs y una captura por caso.
4. Para sonido real, conectar un dispositivo de salida de audio. Reproducir un WAV/MP3 sintético con tonos distintos y verificar señal audible físicamente (no basta con PlayState/posición). Registrar dispositivo y resultado; no usar Null Renderer.
5. Probar por separado Play, Pause, Stop, seek, apertura de archivo inválido y recuperación. Verificar número/orden de `OpenStateChange`, `PlayStateChange` y `EndOfStream`, sin duplicados ni EOS al detener manualmente.
6. Reproducir tres fixtures simultáneamente en tres objetos. Confirmar audio/estado/posición separados por objeto y que finalizar, detener o fallar uno no altera los otros.
7. Con el código original recuperado, probar secuencia de dos o más pistas y modos A/B/C/D en una copia aislada de Gold; documentar cada modo por separado. Sin esos fuentes y una instalación autorizada no se puede atribuir a los modos un comportamiento esperado.
8. Repetir todos los casos en Windows 10 y Windows 11; adjuntar logs, vídeos/capturas, hardware y fallos. El protocolo es pendiente hasta que un operador complete la ejecución y archive evidencia.

## Código VB6 original todavía requerido

En el árbol de las ramas `main` y `work/activex-compat-investigation` no aparecen fuentes `.frm`, `.bas`, `.vbp` ni el typelib binario original. La documentación existente nombra `frmPlayer`, `frmAuto_A`, `frmAuto_B`, `frmAuto_C` y `frmAuto_D`, pero no incluye sus fuentes. Para analizar los cuatro modos y llamadas del reproductor se requieren:

- `frmPlayer.frm` y su archivo de recursos asociado si existe (`.frx`), con código fuente completo.
- `frmAuto_A.frm`, `frmAuto_B.frm`, `frmAuto_C.frm`, `frmAuto_D.frm` y cualquier `.frx` asociado.
- El proyecto VB6 `.vbp` y los `.bas`/`.cls` que declaren o implementen `tmPlay`, `Play_Gold`, `PlaySello` y `PlaySelloA`, además de los módulos de selección/avance de pista invocados por esos procedimientos. No se asignan nombres de archivo a esos módulos sin recibir el proyecto.
- El typelib exacto `MSDXM.OCX` 1.0 usado por la aplicación o una extracción reproducible de sus interfaces, DISPIDs, parámetros y flags; y una copia de prueba autorizada del formulario/proyecto que permita revisar persistencia OLE de las tres instancias.

Los archivos originales pueden compartirse en un ZIP de fuentes protegido o subirse a una rama de este repositorio que no contenga bases de datos, música ni datos personales. No subir `Gold.exe`, `Gold.INI`, `DBMusica.mdb` ni medios de producción.
