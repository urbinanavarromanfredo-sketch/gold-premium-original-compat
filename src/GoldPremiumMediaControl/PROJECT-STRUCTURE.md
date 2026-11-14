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

El objeto final no debe declarar `IMediaPlayer2` como una interfaz dual improvisada. El inventario original informa `TKIND_DISPATCH`; Microsoft documenta que `IDispatchImpl` se orienta a interfaces duales. Debe conservarse un `IDispatch` Automation con el type information `TKIND_DISPATCH` correspondiente, o demostrarse con el typelib original que existe otra vía compatible.
