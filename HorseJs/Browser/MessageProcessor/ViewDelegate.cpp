#include "ViewDelegate.h"
#include "WindowPopupDelegate.h"
/// <summary>
/// ��ǰҳ�浯���´���ʱ�˷�����ִ��
/// </summary>
/// <param name="browserView"></param>
/// <param name="popupBrowserView"></param>
/// <param name="isDevtools"></param>
/// <returns></returns>
bool ViewDelegate::OnPopupBrowserViewCreated(CefRefPtr<CefBrowserView> browserView, CefRefPtr<CefBrowserView> popupBrowserView, bool isDevtools)
{
    //todo isDevtoolsû����
    //todo window.open���Ĳ��������
    CefWindow::CreateTopLevelWindow(new WindowPopupDelegate(popupBrowserView));
    return true;
}
void ViewDelegate::OnBrowserDestroyed(CefRefPtr<CefBrowserView> browser_view, CefRefPtr<CefBrowser> browser) {
    int i = 0;
}