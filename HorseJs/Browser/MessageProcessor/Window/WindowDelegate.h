#pragma once
#include "include/views/cef_window.h"
#include "include/views/cef_browser_view.h"
#include "../../json/json.hpp"
#include <list>
class WindowDelegate : public CefWindowDelegate
{
public:
    explicit WindowDelegate(const nlohmann::json& config);
    explicit WindowDelegate(CefRefPtr<CefBrowserView> browserView, bool isDevTool);
    bool IsFrameless(CefRefPtr<CefWindow> window) override;
    void OnWindowCreated(CefRefPtr<CefWindow> window) override;
    void OnWindowDestroyed(CefRefPtr<CefWindow> window) override;
    CefRect GetInitialBounds(CefRefPtr<CefWindow> window) override;
    bool CanClose(CefRefPtr<CefWindow> window) override;
    WindowDelegate(const WindowDelegate&) = delete;
    WindowDelegate& operator=(const WindowDelegate&) = delete;
private:
    nlohmann::json config;
    bool isDevTool = false;
    std::list<CefRefPtr<CefBrowserView>> views;
    IMPLEMENT_REFCOUNTING(WindowDelegate);
};

