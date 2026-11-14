#include "stdafx.h"
#include "GoldPremiumMediaControl.h"

class CGoldPremiumMediaModule final :
    public ATL::CAtlDllModuleT<CGoldPremiumMediaModule>
{
};

CGoldPremiumMediaModule _AtlModule;

OBJECT_ENTRY_AUTO(CLSID_MediaPlayer, CMediaPlayer)

extern "C" BOOL WINAPI DllMain(HINSTANCE, DWORD reason, LPVOID reserved)
{
    return _AtlModule.DllMain(reason, reserved);
}

extern "C" __declspec(dllexport) HRESULT WINAPI DllCanUnloadNow()
{
    return _AtlModule.DllCanUnloadNow();
}

extern "C" __declspec(dllexport) HRESULT WINAPI DllGetClassObject(
    REFCLSID classId,
    REFIID interfaceId,
    LPVOID* object)
{
    return _AtlModule.DllGetClassObject(classId, interfaceId, object);
}
