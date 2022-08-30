#pragma once
#include "include/views/cef_window.h"
#include "include/views/cef_browser_view.h"
#include "../../json/json.hpp"
class WindowOverlayViewDelegate : public CefWindowDelegate
{
public:
    explicit WindowOverlayViewDelegate(const nlohmann::json& config);
    bool IsFrameless(CefRefPtr<CefWindow> window) override;
    void OnWindowCreated(CefRefPtr<CefWindow> window) override;
    void OnWindowDestroyed(CefRefPtr<CefWindow> window) override;
    CefRect GetInitialBounds(CefRefPtr<CefWindow> window) override;
    bool CanClose(CefRefPtr<CefWindow> window) override;
    WindowOverlayViewDelegate(const WindowOverlayViewDelegate&) = delete;
    WindowOverlayViewDelegate& operator=(const WindowOverlayViewDelegate&) = delete;
private:
    nlohmann::json config;
    bool isDevTool = false;
    std::vector<CefRefPtr<CefBrowserView>> views;
    IMPLEMENT_REFCOUNTING(WindowOverlayViewDelegate);
};

