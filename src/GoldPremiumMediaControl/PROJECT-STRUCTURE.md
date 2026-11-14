# Estructura prevista del control ActiveX de producción

Esta es la estructura que se completará en F1–F3. Los archivos de producción no se presentan como implementados todavía; se evita generar código con firmas COM adivinadas.

```text
src/GoldPremiumMediaControl/
  GoldPremiumMediaControl.vcxproj       # DLL ATL, Configuration=Release, Platform=Win32
  GoldPremiumMediaControl.idl           # LIBID/CLSID y Automation/event dispinterfaces
  GoldPremiumMediaControl.h             # CComControl + mapas COM/OLE
  GoldPremiumMediaControl.cpp           # activación, persistencia y ventana del control
  MediaPlayerDispatch.h/.cpp            # GetTypeInfo/GetIDsOfNames/Invoke con DISPIDs reales
  MediaPlayerEvents.h/.cpp              # IConnectionPointContainer y eventos salientes
  MediaPlayerPersistence.h/.cpp         # StreamInit/Storage/PropertyBag y datos persistidos
  PlaybackBackend.h                     # contrato interno independiente del COM
  PlaybackBackendMF.cpp                 # backend nativo elegido solo tras validar formatos/estados
  tests/
    HostVb6Container/                    # host x86 que reproduce el ciclo de contención
    PlaybackContract/                    # pruebas estados, posiciones y fin de medio
```

## Regla importante de diseño

El objeto final debe declarar `IMediaPlayer2` con la forma dual y la herencia
del Type Library histórico de `MSDXM.OCX` 1.0; no como una dispinterface
inventada. Los imports disponibles indican `IMediaPlayer2 : IMediaPlayer`.
La evidencia y la discrepancia con el inventario V4 están documentadas en
[`docs/06-EVIDENCIA-TYPELIB.md`](../../docs/06-EVIDENCIA-TYPELIB.md). La
persistencia real de VB6 sigue pendiente.
