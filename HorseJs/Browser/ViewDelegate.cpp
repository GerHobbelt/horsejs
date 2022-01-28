#include "ViewDelegate.h"
bool ViewDelegate::OnPopupBrowserViewCreated(CefRefPtr<CefBrowserView> browser_view, CefRefPtr<CefBrowserView> popup_browser_view, bool is_devtools)
{
    CefWindow::CreateTopLevelWindow(new WindowDelegate(popup_browser_view));
    return true;
}
