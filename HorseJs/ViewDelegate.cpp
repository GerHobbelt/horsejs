#include "ViewDelegate.h"
#include "WindowDelegate.h"
// ��ǰҳ�浯���´���ʱ�˷�����ִ��
bool ViewDelegate::OnPopupBrowserViewCreated(CefRefPtr<CefBrowserView> browserView, CefRefPtr<CefBrowserView> popupBrowserView, bool isDevtools)
{
    CefWindow::CreateTopLevelWindow(new WindowDelegate(popupBrowserView,isDevtools));
    return true;
}