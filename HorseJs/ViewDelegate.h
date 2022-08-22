#pragma once
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
class ViewDelegate : public CefBrowserViewDelegate
{
public:
    ViewDelegate() = default;
    ViewDelegate(const ViewDelegate&) = delete;
    ViewDelegate& operator=(const ViewDelegate&) = delete;
    // 当前页面弹出新窗口时此方法被执行
    bool OnPopupBrowserViewCreated(CefRefPtr<CefBrowserView> browser_view, CefRefPtr<CefBrowserView> popup_browser_view, bool is_devtools) override;
private:
    IMPLEMENT_REFCOUNTING(ViewDelegate);
};
