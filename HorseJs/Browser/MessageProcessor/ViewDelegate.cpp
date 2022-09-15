#include "ViewDelegate.h"
#include "WindowPopupDelegate.h"
/// <summary>
/// 当前页面弹出新窗口时此方法被执行
/// </summary>
/// <param name="browserView"></param>
/// <param name="popupBrowserView"></param>
/// <param name="isDevtools"></param>
/// <returns></returns>
bool ViewDelegate::OnPopupBrowserViewCreated(CefRefPtr<CefBrowserView> browserView, CefRefPtr<CefBrowserView> popupBrowserView, bool isDevtools)
{
    //todo isDevtools没用上
    //todo window.open传的参数在哪里？
    CefWindow::CreateTopLevelWindow(new WindowPopupDelegate(popupBrowserView));
    return true;
}
void ViewDelegate::OnBrowserDestroyed(CefRefPtr<CefBrowserView> browser_view, CefRefPtr<CefBrowser> browser) {
    int i = 0;
}