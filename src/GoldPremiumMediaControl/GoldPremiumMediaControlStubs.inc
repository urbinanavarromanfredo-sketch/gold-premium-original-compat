    HRESULT STDMETHODCALLTYPE get_ImageSourceWidth(LONG* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ImageSourceHeight(LONG* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_MarkerCount(LONG* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_CanScan(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_CanSeek(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_CanSeekToMarkers(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_CurrentMarker(LONG* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_CurrentMarker(LONG newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_SourceLink(BSTR* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_CreationDate(DATE* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ErrorCorrection(BSTR* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_Bandwidth(LONG* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_SourceProtocol(LONG* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ReceivedPackets(LONG* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_RecoveredPackets(LONG* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_LostPackets(LONG* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ReceptionQuality(LONG* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_BufferingCount(LONG* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_IsBroadcast(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_BufferingProgress(LONG* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ChannelName(BSTR* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ChannelDescription(BSTR* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ChannelURL(BSTR* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ContactAddress(BSTR* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ContactPhone(BSTR* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ContactEmail(BSTR* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_BufferingTime(DOUBLE* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_BufferingTime(DOUBLE newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_AutoStart(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_AutoStart(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_AutoRewind(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_AutoRewind(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_Rate(DOUBLE* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_Rate(DOUBLE newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_SendKeyboardEvents(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_SendKeyboardEvents(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_SendMouseClickEvents(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_SendMouseClickEvents(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_SendMouseMoveEvents(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_SendMouseMoveEvents(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_PlayCount(LONG* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_PlayCount(LONG newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ClickToPlay(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_ClickToPlay(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_AllowScan(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_AllowScan(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_EnableContextMenu(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_EnableContextMenu(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_CursorType(LONG* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_CursorType(LONG newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_CodecCount(LONG* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_AllowChangeDisplaySize(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_AllowChangeDisplaySize(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_IsDurationValid(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_SendWarningEvents(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_SendWarningEvents(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_SendErrorEvents(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_SendErrorEvents(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_DisplaySize(MPDisplaySizeConstants* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_DisplaySize(MPDisplaySizeConstants newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_InvokeURLs(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_InvokeURLs(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_BaseURL(BSTR* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_BaseURL(BSTR newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_DefaultFrame(BSTR* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_DefaultFrame(BSTR newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_HasError(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ErrorDescription(BSTR* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ErrorCode(LONG* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_AnimationAtStart(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_AnimationAtStart(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_TransparentAtStart(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_TransparentAtStart(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ReadyState(MPReadyStateConstants* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_SelectionStart(DOUBLE* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_SelectionStart(DOUBLE newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_SelectionEnd(DOUBLE* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_SelectionEnd(DOUBLE newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ShowDisplay(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_ShowDisplay(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ShowControls(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_ShowControls(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ShowPositionControls(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_ShowPositionControls(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ShowTracker(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_ShowTracker(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_EnablePositionControls(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_EnablePositionControls(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_EnableTracker(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_EnableTracker(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_Enabled(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_Enabled(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_DisplayForeColor(VB_OLE_COLOR* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_DisplayForeColor(VB_OLE_COLOR newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_DisplayBackColor(VB_OLE_COLOR* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_DisplayBackColor(VB_OLE_COLOR newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_DisplayMode(MPDisplayModeConstants* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_DisplayMode(MPDisplayModeConstants newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_VideoBorder3D(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_VideoBorder3D(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_VideoBorderWidth(LONG* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_VideoBorderWidth(LONG newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_VideoBorderColor(VB_OLE_COLOR* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_VideoBorderColor(VB_OLE_COLOR newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ShowGotoBar(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_ShowGotoBar(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ShowStatusBar(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_ShowStatusBar(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ShowCaptioning(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_ShowCaptioning(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ShowAudioControls(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_ShowAudioControls(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_CaptioningID(BSTR* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_CaptioningID(BSTR newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_Mute(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_Mute(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_CanPreview(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_PreviewMode(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_PreviewMode(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_HasMultipleItems(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_Language(LONG* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_Language(LONG newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_AudioStream(LONG* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_AudioStream(LONG newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_SAMIStyle(BSTR* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_SAMIStyle(BSTR newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_SAMILang(BSTR* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_SAMILang(BSTR newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_SAMIFileName(BSTR* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_SAMIFileName(BSTR newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_StreamCount(LONG* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ClientId(BSTR* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ConnectionSpeed(LONG* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_AutoSize(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_AutoSize(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_EnableFullScreenControls(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_EnableFullScreenControls(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_ActiveMovie(IDispatch** pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_NSPlay(IDispatch** pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_WindowlessVideo(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE put_WindowlessVideo(VARIANT_BOOL newValue) noexcept
    {
        UNREFERENCED_PARAMETER(newValue);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE GetMarkerTime(LONG MarkerNum, DOUBLE* pRetVal) noexcept
    {
        UNREFERENCED_PARAMETER(MarkerNum);
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE GetMarkerName(LONG MarkerNum, BSTR* pRetVal) noexcept
    {
        UNREFERENCED_PARAMETER(MarkerNum);
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE AboutBox() noexcept
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE GetCodecInstalled(LONG CodecNum, VARIANT_BOOL* pRetVal) noexcept
    {
        UNREFERENCED_PARAMETER(CodecNum);
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE GetCodecDescription(LONG CodecNum, BSTR* pRetVal) noexcept
    {
        UNREFERENCED_PARAMETER(CodecNum);
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE GetCodecURL(LONG CodecNum, BSTR* pRetVal) noexcept
    {
        UNREFERENCED_PARAMETER(CodecNum);
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE GetMoreInfoURL(MPMoreInfoType MoreInfoType, BSTR* pRetVal) noexcept
    {
        UNREFERENCED_PARAMETER(MoreInfoType);
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE GetMediaInfoString(MPMediaInfoType MediaInfoType, BSTR* pRetVal) noexcept
    {
        UNREFERENCED_PARAMETER(MediaInfoType);
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE Cancel() noexcept
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE IsSoundCardEnabled(VARIANT_BOOL* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE Next() noexcept
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE Previous() noexcept
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE StreamSelect(LONG StreamNum) noexcept
    {
        UNREFERENCED_PARAMETER(StreamNum);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE FastForward() noexcept
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE FastReverse() noexcept
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE GetStreamName(LONG StreamNum, BSTR* pRetVal) noexcept
    {
        UNREFERENCED_PARAMETER(StreamNum);
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE GetStreamGroup(LONG StreamNum, LONG* pRetVal) noexcept
    {
        UNREFERENCED_PARAMETER(StreamNum);
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE GetStreamSelected(LONG StreamNum, VARIANT_BOOL* pRetVal) noexcept
    {
        UNREFERENCED_PARAMETER(StreamNum);
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_DVD(IMediaPlayerDvd** pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE get_EntryCount(LONG* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE GetMediaParameter(LONG EntryNum, BSTR bstrParameterName, BSTR* pRetVal) noexcept
    {
        UNREFERENCED_PARAMETER(EntryNum);
        UNREFERENCED_PARAMETER(bstrParameterName);
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE GetMediaParameterName(LONG EntryNum, LONG Index, BSTR* pRetVal) noexcept
    {
        UNREFERENCED_PARAMETER(EntryNum);
        UNREFERENCED_PARAMETER(Index);
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = nullptr;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE GetCurrentEntry(LONG* pRetVal) noexcept
    {
        if (pRetVal == nullptr) return E_POINTER;
        *pRetVal = 0;
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE SetCurrentEntry(LONG EntryNumber) noexcept
    {
        UNREFERENCED_PARAMETER(EntryNumber);
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE ShowDialog(MPShowDialogConstants mpDialogIndex) noexcept
    {
        UNREFERENCED_PARAMETER(mpDialogIndex);
        return E_NOTIMPL;
    }
