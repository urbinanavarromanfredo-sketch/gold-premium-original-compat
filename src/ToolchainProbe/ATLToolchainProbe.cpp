// This DLL is intentionally only a toolchain probe.
// It is NOT the Gold Premium ActiveX replacement and must never be installed in Gold.
#include <windows.h>
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>

static_assert(sizeof(void*) == 4, "This project must be compiled for Win32/x86.");

class CGoldPremiumProbeModule final
    : public ATL::CAtlDllModuleT<CGoldPremiumProbeModule> {
};

CGoldPremiumProbeModule _AtlModule;

extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    (void)hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
    return _AtlModule.DllCanUnloadNow();
}

extern "C" HRESULT __stdcall DllGetClassObject(
    REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    // There are intentionally no COM class objects in this probe.
    // The real control will add its ATL object map after the COM contract is complete.
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}
