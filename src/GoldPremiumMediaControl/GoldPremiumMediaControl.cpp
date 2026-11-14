#include "stdafx.h"
#include "GoldPremiumMediaControl.h"
#include <cmath>
#include <cstdio>
#include <limits>

namespace
{
    constexpr LONG kGraphNotifyMessage = WM_APP + 0x3D1;
    constexpr REFERENCE_TIME kReferenceTimePerSecond = 10'000'000;
    constexpr LONG kOpenStateClosed = 0;
    constexpr LONG kOpenStateOpen = 6;
    constexpr WCHAR kTypeLibraryResourceSuffix[] = L"\\101";
    constexpr CLSID kNullRendererClassId =
        {0xC1F400A4, 0x3F08, 0x11D3, {0x9F, 0x0B, 0x00, 0x60, 0x08, 0x03, 0x9E, 0x37}};

    void TraceFailure(const char* operation, HRESULT hr) noexcept
    {
        std::fprintf(stderr, "%s failed: 0x%08lx\n", operation, static_cast<unsigned long>(hr));
    }

    HRESULT LoadEmbeddedTypeInfo(REFGUID typeInfoId, ITypeInfo** typeInfo) noexcept
    {
        if (typeInfo == nullptr)
        {
            return E_POINTER;
        }
        *typeInfo = nullptr;

        HMODULE module = nullptr;
        if (!GetModuleHandleExW(
                GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                reinterpret_cast<LPCWSTR>(&LoadEmbeddedTypeInfo),
                &module))
        {
            return HRESULT_FROM_WIN32(GetLastError());
        }

        WCHAR modulePath[32768]{};
        const DWORD pathLength = GetModuleFileNameW(module, modulePath, ARRAYSIZE(modulePath));
        if (pathLength == 0 || pathLength >= ARRAYSIZE(modulePath))
        {
            return HRESULT_FROM_WIN32(pathLength == 0 ? GetLastError() : ERROR_INSUFFICIENT_BUFFER);
        }
        if (wcscat_s(modulePath, ARRAYSIZE(modulePath), kTypeLibraryResourceSuffix) != 0)
        {
            return HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER);
        }

        ATL::CComPtr<ITypeLib> typeLibrary;
        HRESULT hr = LoadTypeLibEx(modulePath, REGKIND_NONE, &typeLibrary);
        if (FAILED(hr))
        {
            return hr;
        }
        return typeLibrary->GetTypeInfoOfGuid(typeInfoId, typeInfo);
    }

    HRESULT RenderAudioWithoutDevice(IGraphBuilder* graph, BSTR fileName) noexcept
    {
        if (graph == nullptr)
        {
            return E_POINTER;
        }

        ATL::CComPtr<IBaseFilter> source;
        HRESULT hr = graph->AddSourceFilter(fileName, L"Media file", &source);
        if (FAILED(hr))
        {
            TraceFailure("AddSourceFilter", hr);
            return hr;
        }

        ATL::CComPtr<IBaseFilter> nullRenderer;
        hr = CoCreateInstance(
            kNullRendererClassId, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&nullRenderer));
        if (FAILED(hr))
        {
            TraceFailure("CoCreateInstance Null Renderer", hr);
            return hr;
        }
        hr = graph->AddFilter(nullRenderer, L"Null audio renderer");
        if (FAILED(hr))
        {
            TraceFailure("AddFilter Null Renderer", hr);
            return hr;
        }

        ATL::CComPtr<IFilterGraph2> graph2;
        hr = graph->QueryInterface(IID_PPV_ARGS(&graph2));
        if (FAILED(hr))
        {
            TraceFailure("QueryInterface IFilterGraph2", hr);
            return hr;
        }

        ATL::CComPtr<IEnumPins> pins;
        hr = source->EnumPins(&pins);
        if (FAILED(hr))
        {
            TraceFailure("Source EnumPins", hr);
            return hr;
        }

        ULONG renderedOutputs = 0;
        ATL::CComPtr<IPin> pin;
        while (pins->Next(1, &pin, nullptr) == S_OK)
        {
            PIN_DIRECTION direction = PINDIR_INPUT;
            hr = pin->QueryDirection(&direction);
            if (FAILED(hr))
            {
                TraceFailure("Source pin QueryDirection", hr);
                return hr;
            }
            if (direction == PINDIR_OUTPUT)
            {
                hr = graph2->RenderEx(
                    pin,
                    AM_RENDEREX_RENDERTOEXISTINGRENDERERS,
                    nullptr);
                if (FAILED(hr))
                {
                    TraceFailure("IFilterGraph2::RenderEx", hr);
                    return hr;
                }
                ++renderedOutputs;
            }
            pin.Release();
        }
        if (renderedOutputs == 0)
        {
            TraceFailure("Render media outputs", VFW_E_NOT_FOUND);
            return VFW_E_NOT_FOUND;
        }
        return S_OK;
    }
}

CMediaPlayer::CMediaPlayer() noexcept
    : m_playState(mpStopped),
      m_openState(0),
      m_volume(0),
      m_balance(0),
      m_sendOpenStateChangeEvents(VARIANT_TRUE),
      m_sendPlayStateChangeEvents(VARIANT_TRUE)
{
    m_notifyWindow.owner = this;
}

CMediaPlayer::~CMediaPlayer()
{
    FinalRelease();
}

HRESULT CMediaPlayer::FinalConstruct() noexcept
{
    HRESULT hr = LoadEmbeddedTypeInfo(CLSID_MediaPlayer, &m_classTypeInfo);
    if (SUCCEEDED(hr))
    {
        hr = LoadEmbeddedTypeInfo(IID_IMediaPlayer2, &m_dispatchTypeInfo);
    }
    if (FAILED(hr))
    {
        return hr;
    }

    if (m_notifyWindow.Create(HWND_MESSAGE) == nullptr)
    {
        const DWORD error = GetLastError();
        return HRESULT_FROM_WIN32(error == ERROR_SUCCESS ? ERROR_NOT_ENOUGH_MEMORY : error);
    }

    return S_OK;
}

void CMediaPlayer::FinalRelease() noexcept
{
    CloseGraph();
    m_notifyWindow.owner = nullptr;
    if (m_notifyWindow.IsWindow())
    {
        m_notifyWindow.DestroyWindow();
    }
}

HRESULT CMediaPlayer::OnDraw(ATL_DRAWINFO& drawInfo)
{
    HBRUSH brush = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    const RECT* bounds = reinterpret_cast<const RECT*>(drawInfo.prcBounds);
    return brush != nullptr && bounds != nullptr && FillRect(drawInfo.hdcDraw, bounds, brush)
        ? S_OK
        : HRESULT_FROM_WIN32(GetLastError());
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::GetTypeInfoCount(UINT* count) noexcept
{
    if (count == nullptr)
    {
        return E_POINTER;
    }
    *count = 1;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::GetTypeInfo(
    UINT index, LCID, ITypeInfo** typeInfo) noexcept
{
    if (typeInfo == nullptr)
    {
        return E_POINTER;
    }
    *typeInfo = nullptr;
    if (index != 0)
    {
        return DISP_E_BADINDEX;
    }
    return m_dispatchTypeInfo.CopyTo(typeInfo);
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::GetIDsOfNames(
    REFIID interfaceId, LPOLESTR* names, UINT nameCount, LCID, DISPID* dispIds) noexcept
{
    if (!IsEqualIID(interfaceId, IID_NULL))
    {
        return DISP_E_UNKNOWNINTERFACE;
    }
    return m_dispatchTypeInfo->GetIDsOfNames(names, nameCount, dispIds);
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::Invoke(
    DISPID dispId,
    REFIID interfaceId,
    LCID,
    WORD flags,
    DISPPARAMS* parameters,
    VARIANT* result,
    EXCEPINFO* exceptionInfo,
    UINT* argumentError) noexcept
{
    if (!IsEqualIID(interfaceId, IID_NULL))
    {
        return DISP_E_UNKNOWNINTERFACE;
    }
    return m_dispatchTypeInfo->Invoke(
        static_cast<IMediaPlayer2*>(this), dispId, flags, parameters,
        result, exceptionInfo, argumentError);
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::GetClassInfo(ITypeInfo** typeInfo) noexcept
{
    if (typeInfo == nullptr)
    {
        return E_POINTER;
    }
    *typeInfo = nullptr;
    return m_classTypeInfo.CopyTo(typeInfo);
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::GetGUID(DWORD guidKind, GUID* guid) noexcept
{
    if (guid == nullptr)
    {
        return E_POINTER;
    }
    if (guidKind != GUIDKIND_DEFAULT_SOURCE_DISP_IID)
    {
        return E_INVALIDARG;
    }
    *guid = DIID__MediaPlayerEvents;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::get_CurrentPosition(DOUBLE* value) noexcept
{
    return GetPosition(value, false);
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::put_CurrentPosition(DOUBLE value) noexcept
{
    if (!std::isfinite(value) || value < 0.0 ||
        value > static_cast<DOUBLE>(std::numeric_limits<REFERENCE_TIME>::max()) /
            static_cast<DOUBLE>(kReferenceTimePerSecond))
    {
        return E_INVALIDARG;
    }
    if (!m_mediaSeeking)
    {
        return VFW_E_NOT_CONNECTED;
    }

    LONGLONG position = static_cast<LONGLONG>(value * kReferenceTimePerSecond);
    return m_mediaSeeking->SetPositions(
        &position,
        AM_SEEKING_AbsolutePositioning,
        nullptr,
        AM_SEEKING_NoPositioning);
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::get_Duration(DOUBLE* value) noexcept
{
    return GetPosition(value, true);
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::get_FileName(BSTR* value) noexcept
{
    if (value == nullptr)
    {
        return E_POINTER;
    }
    *value = nullptr;
    return m_fileName.CopyTo(value);
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::put_FileName(BSTR value) noexcept
{
    if (value == nullptr || value[0] == L'\0')
    {
        CloseGraph();
        m_fileName.Empty();
        return S_OK;
    }
    return OpenGraph(value);
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::get_OpenState(LONG* value) noexcept
{
    if (value == nullptr)
    {
        return E_POINTER;
    }
    *value = m_openState;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::get_PlayState(MPPlayStateConstants* value) noexcept
{
    if (value == nullptr)
    {
        return E_POINTER;
    }
    *value = m_playState;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::get_SendOpenStateChangeEvents(VARIANT_BOOL* value) noexcept
{
    if (value == nullptr)
    {
        return E_POINTER;
    }
    *value = m_sendOpenStateChangeEvents;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::put_SendOpenStateChangeEvents(VARIANT_BOOL value) noexcept
{
    m_sendOpenStateChangeEvents = value == VARIANT_FALSE ? VARIANT_FALSE : VARIANT_TRUE;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::get_SendPlayStateChangeEvents(VARIANT_BOOL* value) noexcept
{
    if (value == nullptr)
    {
        return E_POINTER;
    }
    *value = m_sendPlayStateChangeEvents;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::put_SendPlayStateChangeEvents(VARIANT_BOOL value) noexcept
{
    m_sendPlayStateChangeEvents = value == VARIANT_FALSE ? VARIANT_FALSE : VARIANT_TRUE;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::get_Volume(LONG* value) noexcept
{
    if (value == nullptr)
    {
        return E_POINTER;
    }
    *value = m_volume;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::put_Volume(LONG value) noexcept
{
    if (value < -10000 || value > 0)
    {
        return E_INVALIDARG;
    }
    if (m_basicAudio)
    {
        const HRESULT hr = m_basicAudio->put_Volume(value);
        if (FAILED(hr))
        {
            return hr;
        }
    }
    m_volume = value;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::get_Balance(LONG* value) noexcept
{
    if (value == nullptr)
    {
        return E_POINTER;
    }
    *value = m_balance;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::put_Balance(LONG value) noexcept
{
    if (value < -10000 || value > 10000)
    {
        return E_INVALIDARG;
    }
    if (m_basicAudio)
    {
        const HRESULT hr = m_basicAudio->put_Balance(value);
        if (FAILED(hr))
        {
            return hr;
        }
    }
    m_balance = value;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::Open(BSTR fileName) noexcept
{
    return put_FileName(fileName);
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::Play() noexcept
{
    if (!m_mediaControl)
    {
        return VFW_E_NOT_CONNECTED;
    }
    const HRESULT hr = m_mediaControl->Run();
    if (SUCCEEDED(hr))
    {
        SetPlayState(mpPlaying);
    }
    return hr;
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::Pause() noexcept
{
    if (!m_mediaControl)
    {
        return VFW_E_NOT_CONNECTED;
    }
    const HRESULT hr = m_mediaControl->Pause();
    if (SUCCEEDED(hr))
    {
        SetPlayState(mpPaused);
    }
    return hr;
}

HRESULT STDMETHODCALLTYPE CMediaPlayer::Stop() noexcept
{
    if (!m_mediaControl)
    {
        return S_OK;
    }
    const HRESULT hr = m_mediaControl->Stop();
    if (SUCCEEDED(hr))
    {
        SetPlayState(mpStopped);
    }
    return hr;
}

HRESULT CMediaPlayer::OpenGraph(BSTR fileName) noexcept
{
    if (fileName == nullptr || fileName[0] == L'\0')
    {
        return E_INVALIDARG;
    }

    CloseGraph();

    ATL::CComPtr<IGraphBuilder> graph;
    HRESULT hr = CoCreateInstance(
        CLSID_FilterGraph,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&graph));
    if (FAILED(hr))
    {
        TraceFailure("Create filter graph", hr);
        return hr;
    }

    bool headlessAudio = false;
    hr = graph->RenderFile(fileName, nullptr);
    if (hr == VFW_E_NO_AUDIO_HARDWARE)
    {
        TraceFailure("RenderFile without audio hardware", hr);
        graph.Release();
        hr = CoCreateInstance(
            CLSID_FilterGraph,
            nullptr,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&graph));
        if (FAILED(hr))
        {
            TraceFailure("Create headless filter graph", hr);
        }
        if (SUCCEEDED(hr))
        {
            hr = RenderAudioWithoutDevice(graph, fileName);
            headlessAudio = SUCCEEDED(hr);
            if (FAILED(hr))
            {
                TraceFailure("RenderAudioWithoutDevice", hr);
            }
        }
    }
    if (FAILED(hr))
    {
        TraceFailure("OpenGraph", hr);
        return hr;
    }

    ATL::CComPtr<IMediaControl> mediaControl;
    ATL::CComPtr<IMediaSeeking> mediaSeeking;
    ATL::CComPtr<IMediaEventEx> mediaEvent;
    ATL::CComPtr<IBasicAudio> basicAudio;
    hr = graph.QueryInterface(&mediaControl);
    if (FAILED(hr))
    {
        TraceFailure("QueryInterface IMediaControl", hr);
        return hr;
    }
    hr = graph.QueryInterface(&mediaSeeking);
    if (FAILED(hr))
    {
        TraceFailure("QueryInterface IMediaSeeking", hr);
        return hr;
    }
    hr = graph.QueryInterface(&mediaEvent);
    if (FAILED(hr))
    {
        TraceFailure("QueryInterface IMediaEventEx", hr);
        return hr;
    }
    graph.QueryInterface(&basicAudio);
    if (headlessAudio)
    {
        basicAudio.Release();
    }

    hr = mediaEvent->SetNotifyWindow(
        reinterpret_cast<OAHWND>(m_notifyWindow.m_hWnd),
        kGraphNotifyMessage,
        reinterpret_cast<LONG_PTR>(this));
    if (FAILED(hr))
    {
        TraceFailure("IMediaEventEx::SetNotifyWindow", hr);
        return hr;
    }

    m_graph = graph;
    m_mediaControl = mediaControl;
    m_mediaSeeking = mediaSeeking;
    m_mediaEvent = mediaEvent;
    m_basicAudio = basicAudio;
    m_fileName = fileName;
    if (m_basicAudio)
    {
        if (FAILED(hr = m_basicAudio->put_Volume(m_volume)) ||
            FAILED(hr = m_basicAudio->put_Balance(m_balance)))
        {
            TraceFailure("Set basic audio properties", hr);
            CloseGraph();
            return hr;
        }
    }

    SetOpenState(kOpenStateOpen);
    return S_OK;
}

void CMediaPlayer::CloseGraph() noexcept
{
    if (m_mediaEvent)
    {
        m_mediaEvent->SetNotifyWindow(0, 0, 0);
    }
    if (m_mediaControl)
    {
        m_mediaControl->Stop();
    }
    m_mediaEvent.Release();
    m_mediaControl.Release();
    m_mediaSeeking.Release();
    m_basicAudio.Release();
    m_graph.Release();
    SetPlayState(mpStopped);
    SetOpenState(kOpenStateClosed);
}

void CMediaPlayer::SetPlayState(MPPlayStateConstants state) noexcept
{
    if (state == m_playState)
    {
        return;
    }
    const LONG oldState = m_playState;
    m_playState = state;
    if (m_sendPlayStateChangeEvents != VARIANT_FALSE)
    {
        FirePlayStateChange(oldState, state);
    }
}

void CMediaPlayer::SetOpenState(LONG state) noexcept
{
    if (state == m_openState)
    {
        return;
    }
    const LONG oldState = m_openState;
    m_openState = state;
    if (m_sendOpenStateChangeEvents != VARIANT_FALSE)
    {
        FireOpenStateChange(oldState, state);
    }
}

void CMediaPlayer::FirePlayStateChange(LONG oldState, LONG newState) noexcept
{
    ATL::CComVariant args[2];
    args[0] = newState;
    args[1] = oldState;
    DISPPARAMS parameters{args, nullptr, 2, 0};
    for (int index = 0; index < m_vec.GetSize(); ++index)
    {
        ATL::CComPtr<IUnknown> sinkUnknown = m_vec.GetAt(index);
        ATL::CComPtr<IDispatch> sink;
        if (sinkUnknown && SUCCEEDED(sinkUnknown->QueryInterface(IID_PPV_ARGS(&sink))))
        {
            sink->Invoke(
                3012,
                IID_NULL,
                LOCALE_USER_DEFAULT,
                DISPATCH_METHOD,
                &parameters,
                nullptr,
                nullptr,
                nullptr);
        }
    }
}

void CMediaPlayer::FireEndOfStream(LONG result) noexcept
{
    ATL::CComVariant argument(result);
    DISPPARAMS parameters{&argument, nullptr, 1, 0};
    for (int index = 0; index < m_vec.GetSize(); ++index)
    {
        ATL::CComPtr<IUnknown> sinkUnknown = m_vec.GetAt(index);
        ATL::CComPtr<IDispatch> sink;
        if (sinkUnknown && SUCCEEDED(sinkUnknown->QueryInterface(IID_PPV_ARGS(&sink))))
        {
            sink->Invoke(
                3002,
                IID_NULL,
                LOCALE_USER_DEFAULT,
                DISPATCH_METHOD,
                &parameters,
                nullptr,
                nullptr,
                nullptr);
        }
    }
}

HRESULT CMediaPlayer::FireOpenStateChange(LONG oldState, LONG newState) noexcept
{
    ATL::CComVariant args[2];
    args[0] = newState;
    args[1] = oldState;
    DISPPARAMS parameters{args, nullptr, 2, 0};
    HRESULT result = S_OK;
    for (int index = 0; index < m_vec.GetSize(); ++index)
    {
        ATL::CComPtr<IUnknown> sinkUnknown = m_vec.GetAt(index);
        ATL::CComPtr<IDispatch> sink;
        if (sinkUnknown && SUCCEEDED(sinkUnknown->QueryInterface(IID_PPV_ARGS(&sink))))
        {
            const HRESULT hr = sink->Invoke(
                3011,
                IID_NULL,
                LOCALE_USER_DEFAULT,
                DISPATCH_METHOD,
                &parameters,
                nullptr,
                nullptr,
                nullptr);
            if (FAILED(hr) && SUCCEEDED(result))
            {
                result = hr;
            }
        }
    }
    return result;
}

HRESULT CMediaPlayer::GetPosition(DOUBLE* value, bool duration) noexcept
{
    if (value == nullptr)
    {
        return E_POINTER;
    }
    *value = 0.0;
    if (!m_mediaSeeking)
    {
        return S_OK;
    }

    LONGLONG position = 0;
    const HRESULT hr = duration
        ? m_mediaSeeking->GetDuration(&position)
        : m_mediaSeeking->GetCurrentPosition(&position);
    if (SUCCEEDED(hr))
    {
        *value = static_cast<DOUBLE>(position) / kReferenceTimePerSecond;
    }
    return hr;
}

void CMediaPlayer::HandleGraphNotify() noexcept
{
    if (!m_mediaEvent)
    {
        return;
    }

    long eventCode = 0;
    LONG_PTR parameter1 = 0;
    LONG_PTR parameter2 = 0;
    while (m_mediaEvent->GetEvent(&eventCode, &parameter1, &parameter2, 0) == S_OK)
    {
        m_mediaEvent->FreeEventParams(eventCode, parameter1, parameter2);
        if (eventCode == EC_COMPLETE)
        {
            SetPlayState(mpStopped);
            FireEndOfStream(static_cast<LONG>(parameter1));
        }
        else if (eventCode == EC_ERRORABORT)
        {
            SetPlayState(mpStopped);
        }
    }
}

LRESULT CMediaPlayerNotifyWindow::OnGraphNotify(UINT, WPARAM, LPARAM, BOOL&)
{
    if (owner != nullptr)
    {
        owner->HandleGraphNotify();
    }
    return 0;
}
