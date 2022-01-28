#pragma once
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "WindowDelegate.h"
class ViewDelegate : public CefBrowserViewDelegate
{
public:
    ViewDelegate() = default;
    bool OnPopupBrowserViewCreated(CefRefPtr<CefBrowserView> browser_view, CefRefPtr<CefBrowserView> popup_browser_view, bool is_devtools) override; 
private:
    IMPLEMENT_REFCOUNTING(ViewDelegate);
    DISALLOW_COPY_AND_ASSIGN(ViewDelegate);
};
