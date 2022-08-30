#pragma once
#include "include/views/cef_window.h"
#include "include/views/cef_browser_view.h"
#include "../../json/json.hpp"
class WindowMultiViewDelegate : public CefWindowDelegate
{
public:
    explicit WindowMultiViewDelegate(const nlohmann::json& config);
    bool IsFrameless(CefRefPtr<CefWindow> window) override;
    void OnWindowCreated(CefRefPtr<CefWindow> window) override;
    void OnWindowDestroyed(CefRefPtr<CefWindow> window) override;
    CefRect GetInitialBounds(CefRefPtr<CefWindow> window) override;
    bool CanClose(CefRefPtr<CefWindow> window) override;
    WindowMultiViewDelegate(const WindowMultiViewDelegate&) = delete;
    WindowMultiViewDelegate& operator=(const WindowMultiViewDelegate&) = delete;
private:
    nlohmann::json config;
    bool isDevTool = false;
    std::vector<CefRefPtr<CefBrowserView>> views;
    IMPLEMENT_REFCOUNTING(WindowMultiViewDelegate);
};

