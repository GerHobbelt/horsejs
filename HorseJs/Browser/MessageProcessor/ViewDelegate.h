#pragma once
#include "include/views/cef_browser_view.h"
class ViewDelegate:public CefBrowserViewDelegate
{
public:
	// ��ǰҳ�浯���´���ʱ�˷�����ִ��
	bool OnPopupBrowserViewCreated(CefRefPtr<CefBrowserView> browser_view, CefRefPtr<CefBrowserView> popup_browser_view, bool is_devtools) override;
private:
	IMPLEMENT_REFCOUNTING(ViewDelegate);
};

