#include <windows.h>
#include <objbase.h>
#include <ocidl.h>
#include <atlbase.h>
#include <atlcom.h>
#include <cstdio>
#include <functional>
#include <new>
#include <string>

namespace
{
    const CLSID CLSID_MediaPlayer =
        {0x22D6F312, 0xB0F6, 0x11D0, {0x94, 0xAB, 0x00, 0x80, 0xC7, 0x4C, 0x7E, 0x95}};
    const IID DIID_MediaPlayerEvents =
        {0x2D3A4C40, 0xE711, 0x11D0, {0x94, 0xAB, 0x00, 0x80, 0xC7, 0x4C, 0x7E, 0x95}};

    constexpr DISPID kFileName = 1026;
    constexpr DISPID kDuration = 1003;
    constexpr DISPID kCurrentPosition = 1027;
    constexpr DISPID kPlayState = 1068;
    constexpr DISPID kSendPlayStateChangeEvents = 1069;
    constexpr DISPID kVolume = 19;
    constexpr DISPID kBalance = 20;
    constexpr DISPID kPlay = 2001;
    constexpr DISPID kPause = 2002;
    constexpr DISPID kStop = 2003;
    constexpr DISPID kOpen = 2010;
    constexpr DISPID kOpenStateChange = 3011;
    constexpr DISPID kEndOfStream = 3002;
    constexpr DISPID kPlayStateChange = 3012;

    bool CheckHr(HRESULT hr, const char* operation)
    {
        if (FAILED(hr))
        {
            std::fprintf(stderr, "%s failed: 0x%08lx\n", operation, static_cast<unsigned long>(hr));
            return false;
        }
        return true;
    }

    HRESULT Invoke(IDispatch* dispatch, DISPID id, WORD flags, VARIANT* arguments,
        UINT argumentCount, VARIANT* result = nullptr)
    {
        DISPPARAMS parameters{arguments, nullptr, argumentCount, 0};
        DISPID namedId = DISPID_PROPERTYPUT;
        if ((flags & DISPATCH_PROPERTYPUT) != 0)
        {
            parameters.rgdispidNamedArgs = &namedId;
            parameters.cNamedArgs = 1;
        }
        return dispatch->Invoke(
            id, IID_NULL, LOCALE_USER_DEFAULT, flags, &parameters, result, nullptr, nullptr);
    }

    bool PutLong(IDispatch* dispatch, DISPID id, LONG value)
    {
        ATL::CComVariant argument(value);
        return CheckHr(Invoke(dispatch, id, DISPATCH_PROPERTYPUT, &argument, 1), "property put");
    }

    bool PutBool(IDispatch* dispatch, DISPID id, VARIANT_BOOL value)
    {
        ATL::CComVariant argument;
        argument.vt = VT_BOOL;
        argument.boolVal = value;
        return CheckHr(Invoke(dispatch, id, DISPATCH_PROPERTYPUT, &argument, 1), "boolean property put");
    }

    bool GetLong(IDispatch* dispatch, DISPID id, LONG* value)
    {
        ATL::CComVariant result;
        if (!CheckHr(Invoke(dispatch, id, DISPATCH_PROPERTYGET, nullptr, 0, &result), "property get") ||
            FAILED(VariantChangeType(&result, &result, 0, VT_I4)))
        {
            return false;
        }
        *value = result.lVal;
        return true;
    }

    bool PutString(IDispatch* dispatch, DISPID id, const std::wstring& value)
    {
        ATL::CComVariant argument(value.c_str());
        return CheckHr(Invoke(dispatch, id, DISPATCH_PROPERTYPUT, &argument, 1), "string property put");
    }

    bool GetString(IDispatch* dispatch, DISPID id, std::wstring* value)
    {
        ATL::CComVariant result;
        if (!CheckHr(Invoke(dispatch, id, DISPATCH_PROPERTYGET, nullptr, 0, &result), "string property get") ||
            FAILED(VariantChangeType(&result, &result, 0, VT_BSTR)))
        {
            return false;
        }
        value->assign(result.bstrVal, SysStringLen(result.bstrVal));
        return true;
    }

    bool GetDouble(IDispatch* dispatch, DISPID id, DOUBLE* value)
    {
        ATL::CComVariant result;
        if (!CheckHr(Invoke(dispatch, id, DISPATCH_PROPERTYGET, nullptr, 0, &result), "numeric property get") ||
            FAILED(VariantChangeType(&result, &result, 0, VT_R8)))
        {
            return false;
        }
        *value = result.dblVal;
        return true;
    }

    bool PutDouble(IDispatch* dispatch, DISPID id, DOUBLE value)
    {
        ATL::CComVariant argument(value);
        return CheckHr(Invoke(dispatch, id, DISPATCH_PROPERTYPUT, &argument, 1), "double property put");
    }

    bool CallWithString(IDispatch* dispatch, DISPID id, const std::wstring& value)
    {
        ATL::CComVariant argument(value.c_str());
        return CheckHr(Invoke(dispatch, id, DISPATCH_METHOD, &argument, 1), "string media method");
    }

    bool CallNoArguments(IDispatch* dispatch, DISPID id)
    {
        return CheckHr(Invoke(dispatch, id, DISPATCH_METHOD, nullptr, 0), "media method");
    }

    class EventSink final : public IDispatch
    {
    public:
        volatile LONG references = 1;
        LONG endOfStreamCount = 0;
        LONG playStateChangeCount = 0;
        LONG openStateChangeCount = 0;
        bool sawOpenStateOpen = false;
        bool sawOpenStateClosed = false;
        bool advanceOnFirstEnd = false;
        bool advanced = false;
        IDispatch* player = nullptr;
        std::wstring nextFile;
        HRESULT callbackResult = S_OK;

        HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** object) override
        {
            if (object == nullptr)
            {
                return E_POINTER;
            }
            *object = nullptr;
            if (iid == IID_IUnknown || iid == IID_IDispatch)
            {
                *object = static_cast<IDispatch*>(this);
                AddRef();
                return S_OK;
            }
            return E_NOINTERFACE;
        }

        ULONG STDMETHODCALLTYPE AddRef() override
        {
            return static_cast<ULONG>(InterlockedIncrement(&references));
        }
        ULONG STDMETHODCALLTYPE Release() override
        {
            const LONG remaining = InterlockedDecrement(&references);
            if (remaining == 0)
            {
                delete this;
            }
            return static_cast<ULONG>(remaining);
        }

        HRESULT STDMETHODCALLTYPE GetTypeInfoCount(UINT* count) override
        {
            if (count == nullptr) return E_POINTER;
            *count = 0;
            return S_OK;
        }

        HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT, LCID, ITypeInfo**) override { return E_NOTIMPL; }
        HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID, LPOLESTR*, UINT, LCID, DISPID*) override
        {
            return E_NOTIMPL;
        }

        HRESULT STDMETHODCALLTYPE Invoke(DISPID id, REFIID, LCID, WORD, DISPPARAMS* parameters,
            VARIANT*, EXCEPINFO*, UINT*) override
        {
            if (id == kPlayStateChange)
            {
                ++playStateChangeCount;
            }
            else if (id == kOpenStateChange && parameters != nullptr && parameters->cArgs == 2)
            {
                ++openStateChangeCount;
                sawOpenStateOpen = sawOpenStateOpen || parameters->rgvarg[0].lVal == 6;
                sawOpenStateClosed = sawOpenStateClosed || parameters->rgvarg[0].lVal == 0;
            }
            else if (id == kEndOfStream)
            {
                ++endOfStreamCount;
                if (advanceOnFirstEnd && !advanced)
                {
                    advanced = true;
                    if (player == nullptr || !PutString(player, kFileName, nextFile) ||
                        !CallNoArguments(player, kPlay))
                    {
                        callbackResult = E_FAIL;
                    }
                }
            }
            return S_OK;
        }
    };

    bool CreatePlayer(ATL::CComPtr<IDispatch>* player)
    {
        IDispatch* raw = nullptr;
        const HRESULT hr = CoCreateInstance(
            CLSID_MediaPlayer, nullptr, CLSCTX_INPROC_SERVER, IID_IDispatch,
            reinterpret_cast<void**>(&raw));
        if (!CheckHr(hr, "CoCreateInstance"))
        {
            return false;
        }
        player->Attach(raw);
        return true;
    }

    bool PumpUntil(const std::function<bool()>& condition, DWORD timeoutMs)
    {
        const ULONGLONG deadline = GetTickCount64() + timeoutMs;
        while (!condition() && GetTickCount64() < deadline)
        {
            MSG message{};
            while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&message);
                DispatchMessageW(&message);
            }
            MsgWaitForMultipleObjectsEx(0, nullptr, 25, QS_ALLINPUT, MWMO_INPUTAVAILABLE);
        }
        return condition();
    }

    bool RunTests(const std::wstring& mp3Path)
    {
        ATL::CComPtr<IDispatch> players[3];
        for (auto& player : players)
        {
            if (!CreatePlayer(&player)) return false;
            ATL::CComPtr<IOleObject> oleObject;
            ATL::CComPtr<IPersistStreamInit> persistence;
            if (!CheckHr(player->QueryInterface(IID_PPV_ARGS(&oleObject)), "QI IOleObject") ||
                !CheckHr(player->QueryInterface(IID_PPV_ARGS(&persistence)), "QI IPersistStreamInit"))
            {
                return false;
            }
        }

        if (!PutLong(players[0], kVolume, -1000) ||
            !PutLong(players[1], kVolume, -2500) ||
            !PutLong(players[2], kVolume, -5000))
        {
            return false;
        }
        LONG volume = 0;
        if (!GetLong(players[0], kVolume, &volume) || volume != -1000 ||
            !GetLong(players[1], kVolume, &volume) || volume != -2500 ||
            !GetLong(players[2], kVolume, &volume) || volume != -5000)
        {
            std::fprintf(stderr, "Three control instances did not retain independent volume values.\n");
            return false;
        }

        if (!PutLong(players[0], kBalance, 1500) ||
            !PutBool(players[0], kSendPlayStateChangeEvents, VARIANT_FALSE) ||
            !PutString(players[0], kFileName, mp3Path))
        {
            return false;
        }
        ATL::CComPtr<IPersistStreamInit> persistence;
        if (!CheckHr(players[0]->QueryInterface(IID_PPV_ARGS(&persistence)), "QI IPersistStreamInit"))
        {
            return false;
        }
        ATL::CComPtr<IStream> stream;
        if (!CheckHr(CreateStreamOnHGlobal(nullptr, TRUE, &stream), "CreateStreamOnHGlobal") ||
            !CheckHr(persistence->Save(stream, TRUE), "IPersistStreamInit::Save"))
        {
            return false;
        }
        LARGE_INTEGER beginning{};
        if (!CheckHr(stream->Seek(beginning, STREAM_SEEK_SET, nullptr), "IStream::Seek") ||
            !CheckHr(persistence->InitNew(), "IPersistStreamInit::InitNew") ||
            !CheckHr(persistence->Load(stream), "IPersistStreamInit::Load"))
        {
            return false;
        }
        std::wstring restoredFile;
        LONG restoredBalance = 0;
        LONG restoredVolume = 0;
        LONG restoredEvents = VARIANT_TRUE;
        if (!GetString(players[0], kFileName, &restoredFile) || restoredFile != mp3Path ||
            !GetLong(players[0], kBalance, &restoredBalance) || restoredBalance != 1500 ||
            !GetLong(players[0], kVolume, &restoredVolume) || restoredVolume != -1000 ||
            !GetLong(players[0], kSendPlayStateChangeEvents, &restoredEvents) ||
            restoredEvents != VARIANT_FALSE)
        {
            std::fprintf(stderr, "Persisted control properties did not round-trip.\n");
            return false;
        }

        EventSink* sinks[3]{};
        ATL::CComPtr<IConnectionPoint> connectionPoints[3];
        DWORD cookies[3]{};
        for (size_t index = 0; index < 3; ++index)
        {
            ATL::CComPtr<IConnectionPointContainer> container;
            if (!CheckHr(players[index]->QueryInterface(IID_PPV_ARGS(&container)), "QI IConnectionPointContainer") ||
                !CheckHr(container->FindConnectionPoint(DIID_MediaPlayerEvents, &connectionPoints[index]), "FindConnectionPoint"))
            {
                return false;
            }
            sinks[index] = new (std::nothrow) EventSink();
            if (sinks[index] == nullptr)
            {
                return false;
            }
            if (!CheckHr(connectionPoints[index]->Advise(sinks[index], &cookies[index]), "IConnectionPoint::Advise"))
            {
                sinks[index]->Release();
                sinks[index] = nullptr;
                return false;
            }
        }

        sinks[0]->player = players[0];
        sinks[0]->nextFile = mp3Path;
        sinks[0]->advanceOnFirstEnd = true;
        for (size_t index = 0; index < 3; ++index)
        {
            if (!PutBool(players[index], kSendPlayStateChangeEvents, VARIANT_TRUE) ||
                (index == 1
                    ? !CallWithString(players[index], kOpen, mp3Path)
                    : !PutString(players[index], kFileName, mp3Path)))
            {
                return false;
            }
        }

        DOUBLE duration = 0.0;
        if (!GetDouble(players[0], kDuration, &duration) || duration <= 0.0)
        {
            std::fprintf(stderr, "The DirectShow graph did not report a positive MP3 duration.\n");
            return false;
        }

        if (!CallNoArguments(players[0], kPlay))
        {
            return false;
        }
        DOUBLE position = 0.0;
        if (!PumpUntil([&]
            {
                return GetDouble(players[0], kCurrentPosition, &position) && position > 0.1;
            }, 3000))
        {
            std::fprintf(stderr, "CurrentPosition did not advance while playing.\n");
            return false;
        }
        if (!CallNoArguments(players[0], kPause))
        {
            return false;
        }
        LONG playState = -1;
        if (!GetLong(players[0], kPlayState, &playState) || playState != 1)
        {
            std::fprintf(stderr, "Pause did not report the paused PlayState.\n");
            return false;
        }
        if (!GetDouble(players[0], kCurrentPosition, &position) || position <= 0.0)
        {
            std::fprintf(stderr, "CurrentPosition did not advance while playing.\n");
            return false;
        }
        if (!CallNoArguments(players[0], kStop) ||
            !GetLong(players[0], kPlayState, &playState) || playState != 0)
        {
            std::fprintf(stderr, "Stop did not report the stopped PlayState.\n");
            return false;
        }
        if (!PutDouble(players[0], kCurrentPosition, 0.0) ||
            !GetDouble(players[0], kCurrentPosition, &position) || position > 0.05)
        {
            std::fprintf(stderr, "CurrentPosition did not seek back to the beginning.\n");
            return false;
        }

        for (auto& player : players)
        {
            if (!CallNoArguments(player, kPlay))
            {
                return false;
            }
        }
        const DWORD waitMs = static_cast<DWORD>((duration * 3000.0) + 10000.0);
        const bool finished = PumpUntil([&]
        {
            return sinks[0]->endOfStreamCount >= 2 &&
                sinks[1]->endOfStreamCount >= 1 &&
                sinks[2]->endOfStreamCount >= 1;
        }, waitMs);

        bool passed = finished;
        if (!finished)
        {
            std::fprintf(stderr, "Timed out waiting for independent EndOfStream notifications.\n");
            passed = false;
        }
        for (auto& player : players)
        {
            if (!PutString(player, kFileName, L""))
            {
                passed = false;
            }
        }
        for (EventSink* sink : sinks)
        {
            if (sink == nullptr) continue;
            if (FAILED(sink->callbackResult))
            {
                std::fprintf(stderr, "The EndOfStream client failed to advance to the next track.\n");
                passed = false;
            }
            if (sink->playStateChangeCount == 0)
            {
                std::fprintf(stderr, "No PlayStateChange event was received.\n");
                passed = false;
            }
            if (sink->openStateChangeCount == 0 || !sink->sawOpenStateOpen ||
                !sink->sawOpenStateClosed)
            {
                std::fprintf(stderr, "OpenStateChange did not report the verified closed/open states.\n");
                passed = false;
            }
        }

        for (size_t index = 0; index < 3; ++index)
        {
            if (cookies[index] != 0)
            {
                connectionPoints[index]->Unadvise(cookies[index]);
            }
            if (sinks[index] != nullptr)
            {
                sinks[index]->Release();
            }
        }

        if (passed)
        {
            std::puts("COM creation, OLE interfaces, three independent instances, property persistence, MP3 playback, pause/stop, PlayStateChange, EndOfStream, and event-driven next-track playback passed.");
        }
        return passed;
    }
}

int wmain(int argc, wchar_t** argv)
{
    if (argc != 2)
    {
        std::fwprintf(stderr, L"Usage: ActiveXContractTests.exe <generated-test.mp3>\n");
        return 2;
    }

    wchar_t modulePath[MAX_PATH]{};
    const DWORD pathLength = GetModuleFileNameW(nullptr, modulePath, MAX_PATH);
    if (pathLength == 0 || pathLength >= MAX_PATH)
    {
        std::fprintf(stderr, "Cannot determine test executable path.\n");
        return 2;
    }
    std::wstring manifestPath(modulePath, pathLength);
    const size_t separator = manifestPath.find_last_of(L"\\/");
    manifestPath.resize(separator == std::wstring::npos ? 0 : separator + 1);
    manifestPath += L"ActiveXContractTests.manifest";

    ACTCTXW activationContext{};
    activationContext.cbSize = sizeof(activationContext);
    activationContext.lpSource = manifestPath.c_str();
    HANDLE context = CreateActCtxW(&activationContext);
    if (context == INVALID_HANDLE_VALUE)
    {
        std::fprintf(stderr, "CreateActCtxW failed: %lu\n", GetLastError());
        return 2;
    }
    ULONG_PTR cookie = 0;
    if (!ActivateActCtx(context, &cookie))
    {
        std::fprintf(stderr, "ActivateActCtx failed: %lu\n", GetLastError());
        ReleaseActCtx(context);
        return 2;
    }

    const HRESULT initResult = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    bool passed = SUCCEEDED(initResult);
    if (!passed)
    {
        std::fprintf(stderr, "CoInitializeEx failed: 0x%08lx\n", static_cast<unsigned long>(initResult));
    }
    else
    {
        passed = RunTests(argv[1]);
        CoUninitialize();
    }

    DeactivateActCtx(0, cookie);
    ReleaseActCtx(context);
    return passed ? 0 : 1;
}
