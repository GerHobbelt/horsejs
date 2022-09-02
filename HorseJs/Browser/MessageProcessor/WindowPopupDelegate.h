#pragma once
#include "include/views/cef_window.h"
#include "include/views/cef_browser_view.h"
#include "../../json/json.hpp"
#include <list>
class WindowPopupDelegate : public CefWindowDelegate
{
public:
    explicit WindowPopupDelegate(CefRefPtr<CefBrowserView> browserView);
    void OnWindowCreated(CefRefPtr<CefWindow> window) override;
    void OnWindowDestroyed(CefRefPtr<CefWindow> window) override;
    CefRect GetInitialBounds(CefRefPtr<CefWindow> window) override;
    bool CanClose(CefRefPtr<CefWindow> window) override;
    WindowPopupDelegate(const WindowPopupDelegate&) = delete;
    WindowPopupDelegate& operator=(const WindowPopupDelegate&) = delete;
private:
    CefRefPtr<CefBrowserView> view;
    IMPLEMENT_REFCOUNTING(WindowPopupDelegate);
};

