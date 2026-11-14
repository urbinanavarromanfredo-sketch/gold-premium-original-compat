# Política de archivos y despliegue

- El repositorio debe ser privado.
- No subir `Gold.exe`, respaldos, `Gold.INI`, `DBMusica.mdb`, carpetas de música, listas de reproducción ni datos de estación.
- Las pruebas futuras deben usar una copia aislada del EXE y audio sintético/de prueba.
- No ejecutar `regsvr32` ni `DllRegisterServer` contra el CLSID original.
- La plantilla de manifiesto no se instala hasta validar la DLL ActiveX y su typelib.
- El paquete de prueba final debe conservar el hash del EXE original y añadir la DLL/manifest por separado; si se parchea el EXE, se requiere una autorización y respaldo separados.
