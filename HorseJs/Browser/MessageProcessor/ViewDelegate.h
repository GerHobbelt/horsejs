#pragma once
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
class ViewDelegate : public CefBrowserViewDelegate
{
public:
    static CefRefPtr<ViewDelegate> getInstance();
    ViewDelegate(const ViewDelegate&) = delete;
    ViewDelegate& operator=(const ViewDelegate&) = delete;
    void OnWindowChanged(CefRefPtr<CefView> view, bool added) override;
    //CefSize GetPreferredSize(CefRefPtr<CefView> view) override;
    // 当前页面弹出新窗口时此方法被执行
    bool OnPopupBrowserViewCreated(CefRefPtr<CefBrowserView> browser_view, CefRefPtr<CefBrowserView> popup_browser_view, bool is_devtools) override;
private:
    ViewDelegate() = default;
    ~ViewDelegate();
    IMPLEMENT_REFCOUNTING(ViewDelegate);
};
