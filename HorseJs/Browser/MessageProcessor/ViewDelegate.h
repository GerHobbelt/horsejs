#pragma once
#include "include/views/cef_browser_view.h"
class ViewDelegate:public CefBrowserViewDelegate
{
public:
	// 当前页面弹出新窗口时此方法被执行
	bool OnPopupBrowserViewCreated(CefRefPtr<CefBrowserView> browser_view, CefRefPtr<CefBrowserView> popup_browser_view, bool is_devtools) override;
private:
	IMPLEMENT_REFCOUNTING(ViewDelegate);
};

