# Control ActiveX real — pendiente de implementación

Esta carpeta reserva el proyecto de producción. No contiene una DLL utilizable todavía.

## Base de clase que debe implementar

- Servidor in-process Win32/x86 con ATL.
- Coclass/CLSID esperado: `{22D6F312-B0F6-11D0-94AB-0080C74C7E95}`.
- Interfaz Automation `IMediaPlayer2` IID `{20D4F5E0-5475-11D2-9774-0000F80855E6}`; el informe la identifica como `TKIND_DISPATCH`.
- Event source `_MediaPlayerEvents` IID `{2D3A4C40-E711-11D0-94AB-0080C74C7E95}`.
- Soporte de OLE hosting, visualización, activación, persistencia y connection points.
- Estado y backend separados por instancia para no mezclar los tres reproductores.

## Condición para comenzar a emitir una DLL de control

No compilar aquí una interfaz aproximada. Primero hay que completar las firmas reales del type library y la persistencia de `frmPlayer`. El workflow inicial construye solamente `ATLToolchainProbe.dll`, que no representa un control ni debe copiarse junto a Gold.
