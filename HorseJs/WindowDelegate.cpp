#include "WindowDelegate.h"
#include "include/cef_app.h"
#include "include/views/cef_display.h"
#include "Config.h"
#include "include/views/cef_box_layout.h"
#include "include/views/cef_fill_layout.h"
#include "include/views/cef_layout.h"
//���ڴ����ɹ�
void WindowDelegate::OnWindowCreated(CefRefPtr<CefWindow> window) {
    window->AddChildView(browserView);
    window->Show();
    browserView->RequestFocus();
    window->SetTitle(L"�����ҵĴ��ڱ���");
    //window->CenterWindow(CefSize(800, 600));
}
//�������ٳɹ�
void WindowDelegate::OnWindowDestroyed(CefRefPtr<CefWindow> window) {
    browserView = nullptr;
}
//���ô���λ�úʹ�С
CefRect WindowDelegate::GetInitialBounds(CefRefPtr<CefWindow> window) {
    CefRefPtr<CefDisplay> display = CefDisplay::GetPrimaryDisplay();
    CefRect rect = display->GetBounds();
    rect.x = (rect.width - 800) / 2;
    rect.y = (rect.height - 600) / 2;
    rect.width = 800;
    rect.height = 600;
    return rect;
}
bool WindowDelegate::IsFrameless(CefRefPtr<CefWindow> window) {
    if (isDevTool) {
        return false;
    }
    return config["framelessWindow"].get<bool>();
}
bool WindowDelegate::CanClose(CefRefPtr<CefWindow> window) {
    bool result = true;
    CefRefPtr<CefBrowser> browser = browserView->GetBrowser();
    if (browser) {
        result = browser->GetHost()->TryCloseBrowser();
    }
    return result;
}
