#include "WindowPopupDelegate.h"
WindowPopupDelegate::WindowPopupDelegate(CefRefPtr<CefBrowserView> browserView) :view(browserView) {
}

/// <summary>
/// ���ڴ����ɹ�
/// </summary>
/// <param name="window"></param>
void WindowPopupDelegate::OnWindowCreated(CefRefPtr<CefWindow> window) {
    window->AddChildView(view);
    window->Show();
}
/// <summary>
/// ���ô���λ�úʹ�С
/// </summary>
/// <param name="window"></param>
/// <returns></returns>
CefRect WindowPopupDelegate::GetInitialBounds(CefRefPtr<CefWindow> window) {
    CefRect rect;
    auto width = 800;
    auto height = 600;
    CefRefPtr<CefDisplay> display = CefDisplay::GetPrimaryDisplay();
    CefRect displayRect = display->GetBounds();
    rect.x = (displayRect.width - width) / 2;
    rect.y = (displayRect.height - height) / 2;
    rect.width = width;
    rect.height = height;
    return rect;
}
/// <summary>
/// �������ٳɹ�
/// </summary>
/// <param name="window"></param>
void WindowPopupDelegate::OnWindowDestroyed(CefRefPtr<CefWindow> window) {
    view = nullptr;
}

/// <summary>
/// ҳ���Ƿ���ֹ���ڹر�
/// </summary>
/// <param name="window"></param>
/// <returns></returns>
bool WindowPopupDelegate::CanClose(CefRefPtr<CefWindow> window) {
    bool result = true;
    CefRefPtr<CefBrowser> browser = view->GetBrowser();
    result = browser->GetHost()->TryCloseBrowser();
    return true;
}