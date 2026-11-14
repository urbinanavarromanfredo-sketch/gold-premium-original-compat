#pragma once

#include "resource.h"
#include "GoldPremiumMediaControl_h.h"
#include <atlctl.h>
#include <dshow.h>

class CMediaPlayer;

class CMediaPlayerNotifyWindow final : public ATL::CWindowImpl<CMediaPlayerNotifyWindow>
{
public:
    DECLARE_WND_CLASS_EX(L"GoldPremiumMediaPlayerNotifyWindow", 0, COLOR_WINDOW)

    CMediaPlayer* owner = nullptr;

    BEGIN_MSG_MAP(CMediaPlayerNotifyWindow)
        MESSAGE_HANDLER(WM_APP + 0x3D1, OnGraphNotify)
    END_MSG_MAP()

    LRESULT OnGraphNotify(UINT, WPARAM, LPARAM, BOOL&);
};
class ATL_NO_VTABLE CMediaPlayer :
    public ATL::CComObjectRootEx<ATL::CComSingleThreadModel>,
    public ATL::CComCoClass<CMediaPlayer, &CLSID_MediaPlayer>,
    public ATL::CComControl<CMediaPlayer>,
    public ATL::IDispatchImpl<IMediaPlayer2, &IID_IMediaPlayer2,
        &LIBID_GoldPremiumMediaPlayerLib, 1, 0>,
    public ATL::IPersistStreamInitImpl<CMediaPlayer>,
    public ATL::IOleControlImpl<CMediaPlayer>,
    public ATL::IOleObjectImpl<CMediaPlayer>,
    public ATL::IOleInPlaceActiveObjectImpl<CMediaPlayer>,
    public ATL::IOleInPlaceObjectWindowlessImpl<CMediaPlayer>,
    public ATL::IViewObjectExImpl<CMediaPlayer>,
    public ATL::IQuickActivateImpl<CMediaPlayer>,
    public ATL::IDataObjectImpl<CMediaPlayer>,
    public ATL::IConnectionPointContainerImpl<CMediaPlayer>,
    public ATL::IConnectionPointImpl<CMediaPlayer, &DIID__MediaPlayerEvents,
        ATL::CComDynamicUnkArray>,
    public ATL::IProvideClassInfo2Impl<&CLSID_MediaPlayer,
        &DIID__MediaPlayerEvents, &LIBID_GoldPremiumMediaPlayerLib>
{
public:
    CMediaPlayer() noexcept;
    ~CMediaPlayer();

    DECLARE_NOT_AGGREGATABLE(CMediaPlayer)
    DECLARE_NO_REGISTRY()
    DECLARE_PROTECT_FINAL_CONSTRUCT()

    HRESULT FinalConstruct() noexcept;
    void FinalRelease() noexcept;
    HRESULT OnDraw(ATL_DRAWINFO& drawInfo);
    HRESULT STDMETHODCALLTYPE get_CurrentPosition(DOUBLE* value) noexcept;
    HRESULT STDMETHODCALLTYPE put_CurrentPosition(DOUBLE value) noexcept;
    HRESULT STDMETHODCALLTYPE get_Duration(DOUBLE* value) noexcept;
    HRESULT STDMETHODCALLTYPE get_FileName(BSTR* value) noexcept;
    HRESULT STDMETHODCALLTYPE put_FileName(BSTR value) noexcept;
    HRESULT STDMETHODCALLTYPE get_OpenState(LONG* value) noexcept;
    HRESULT STDMETHODCALLTYPE get_PlayState(MPPlayStateConstants* value) noexcept;
    HRESULT STDMETHODCALLTYPE get_SendOpenStateChangeEvents(VARIANT_BOOL* value) noexcept;
    HRESULT STDMETHODCALLTYPE put_SendOpenStateChangeEvents(VARIANT_BOOL value) noexcept;
    HRESULT STDMETHODCALLTYPE get_SendPlayStateChangeEvents(VARIANT_BOOL* value) noexcept;
    HRESULT STDMETHODCALLTYPE put_SendPlayStateChangeEvents(VARIANT_BOOL value) noexcept;
    HRESULT STDMETHODCALLTYPE get_Volume(LONG* value) noexcept;
    HRESULT STDMETHODCALLTYPE put_Volume(LONG value) noexcept;
    HRESULT STDMETHODCALLTYPE get_Balance(LONG* value) noexcept;
    HRESULT STDMETHODCALLTYPE put_Balance(LONG value) noexcept;
    HRESULT STDMETHODCALLTYPE Open(BSTR fileName) noexcept;
    HRESULT STDMETHODCALLTYPE Play() noexcept;
    HRESULT STDMETHODCALLTYPE Pause() noexcept;
    HRESULT STDMETHODCALLTYPE Stop() noexcept;

#include "GoldPremiumMediaControlStubs.inc"

    BEGIN_COM_MAP(CMediaPlayer)
        COM_INTERFACE_ENTRY(IMediaPlayer2)
        COM_INTERFACE_ENTRY(IMediaPlayer)
        COM_INTERFACE_ENTRY2(IDispatch, IMediaPlayer2)
        COM_INTERFACE_ENTRY(IConnectionPointContainer)
        COM_INTERFACE_ENTRY(IPersistStreamInit)
        COM_INTERFACE_ENTRY(IOleObject)
        COM_INTERFACE_ENTRY(IOleControl)
        COM_INTERFACE_ENTRY(IOleInPlaceObject)
        COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
        COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
        COM_INTERFACE_ENTRY(IViewObjectEx)
        COM_INTERFACE_ENTRY(IViewObject2)
        COM_INTERFACE_ENTRY(IViewObject)
        COM_INTERFACE_ENTRY(IQuickActivate)
        COM_INTERFACE_ENTRY(IDataObject)
        COM_INTERFACE_ENTRY(IProvideClassInfo)
        COM_INTERFACE_ENTRY(IProvideClassInfo2)
    END_COM_MAP()

    BEGIN_PROP_MAP(CMediaPlayer)
        PROP_DATA_ENTRY("FileName", m_fileName, VT_BSTR)
        PROP_DATA_ENTRY("SendOpenStateChangeEvents", m_sendOpenStateChangeEvents, VT_BOOL)
        PROP_DATA_ENTRY("SendPlayStateChangeEvents", m_sendPlayStateChangeEvents, VT_BOOL)
        PROP_DATA_ENTRY("Volume", m_volume, VT_I4)
        PROP_DATA_ENTRY("Balance", m_balance, VT_I4)
    END_PROP_MAP()

    BEGIN_CONNECTION_POINT_MAP(CMediaPlayer)
        CONNECTION_POINT_ENTRY(DIID__MediaPlayerEvents)
    END_CONNECTION_POINT_MAP()

    DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

private:
    friend class CMediaPlayerNotifyWindow;

    HRESULT OpenGraph(BSTR fileName) noexcept;
    void CloseGraph() noexcept;
    void SetPlayState(MPPlayStateConstants state) noexcept;
    void SetOpenState(LONG state) noexcept;
    void FirePlayStateChange(LONG oldState, LONG newState) noexcept;
    void FireEndOfStream(LONG result) noexcept;
    HRESULT FireOpenStateChange(LONG oldState, LONG newState) noexcept;
    HRESULT GetPosition(DOUBLE* value, bool duration) noexcept;
    void HandleGraphNotify() noexcept;

    ATL::CComBSTR m_fileName;
    CMediaPlayerNotifyWindow m_notifyWindow;
    ATL::CComPtr<IGraphBuilder> m_graph;
    ATL::CComPtr<IMediaControl> m_mediaControl;
    ATL::CComPtr<IMediaSeeking> m_mediaSeeking;
    ATL::CComPtr<IMediaEventEx> m_mediaEvent;
    ATL::CComPtr<IBasicAudio> m_basicAudio;
    MPPlayStateConstants m_playState;
    LONG m_openState;
    LONG m_volume;
    LONG m_balance;
    VARIANT_BOOL m_sendOpenStateChangeEvents;
    VARIANT_BOOL m_sendPlayStateChangeEvents;
};
