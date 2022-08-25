#pragma once
#include "include/views/cef_window.h"
#include "include/views/cef_browser_view.h"
class WindowDelegate : public CefWindowDelegate
{
public:
    explicit WindowDelegate(CefRefPtr<CefBrowserView> browserView, bool isDevTool) : browserView(browserView), isDevTool(isDevTool) {};
    bool IsFrameless(CefRefPtr<CefWindow> window) override;
    void OnWindowCreated(CefRefPtr<CefWindow> window) override;
    void OnWindowDestroyed(CefRefPtr<CefWindow> window) override;
    CefRect GetInitialBounds(CefRefPtr<CefWindow> window) override;
    bool CanClose(CefRefPtr<CefWindow> window) override;
    WindowDelegate(const WindowDelegate&) = delete;
    WindowDelegate& operator=(const WindowDelegate&) = delete;
private:
    bool isDevTool;
    CefRefPtr<CefBrowserView> browserView;
    IMPLEMENT_REFCOUNTING(WindowDelegate);
};

