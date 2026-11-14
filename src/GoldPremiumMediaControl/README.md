# Control ActiveX real — pendiente de implementación

Esta carpeta reserva el proyecto de producción. No contiene una DLL utilizable todavía.

## Base de clase que debe implementar

- Servidor in-process Win32/x86 con ATL.
- Coclass/CLSID esperado: `{22D6F312-B0F6-11D0-94AB-0080C74C7E95}`.
- Interfaz Automation `IMediaPlayer2` IID `{20D4F5E0-5475-11D2-9774-0000F80855E6}`; los imports del Type Library la identifican como dual y derivada de `IMediaPlayer`.
- Event source `_MediaPlayerEvents` IID `{2D3A4C40-E711-11D0-94AB-0080C74C7E95}`.
- Soporte de OLE hosting, visualización, activación, persistencia y connection points.
- Estado y backend separados por instancia para no mezclar los tres reproductores.

## Estado

Esta carpeta aún no contiene implementación. Las firmas de las interfaces y
los eventos estándar se han recuperado de imports públicos coincidentes por
identificadores. Falta cotejarlos con el Type Library original y obtener la
persistencia y el uso real de `frmPlayer`. No se debe compilar ni distribuir
una DLL de producción antes de superar esas verificaciones.
