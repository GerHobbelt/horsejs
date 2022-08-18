#pragma once
#include "include/views/cef_window.h"
#include "include/views/cef_browser_view.h"
class WindowDelegate : public CefWindowDelegate
{
public:
    explicit WindowDelegate(CefRefPtr<CefBrowserView> browser_view) : browser_view_(browser_view) {};
    void OnWindowCreated(CefRefPtr<CefWindow> window) override;
    void OnWindowDestroyed(CefRefPtr<CefWindow> window) override;
    CefRect GetInitialBounds(CefRefPtr<CefWindow> window) override;
    WindowDelegate(const WindowDelegate&) = delete;
    WindowDelegate& operator=(const WindowDelegate&) = delete;
private:
    CefRefPtr<CefBrowserView> browser_view_;
    IMPLEMENT_REFCOUNTING(WindowDelegate);
};

