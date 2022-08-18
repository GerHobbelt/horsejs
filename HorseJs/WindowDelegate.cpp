#include "WindowDelegate.h"
#include "include/cef_app.h"
#include "include/views/cef_display.h"
//���ڴ����ɹ�
void WindowDelegate::OnWindowCreated(CefRefPtr<CefWindow> window) {
    window->AddChildView(browser_view_);
    window->Show();
    browser_view_->RequestFocus();
    window->SetTitle(L"�����ҵĴ��ڱ���");
    //window->CenterWindow(CefSize(800, 600));
}
//�������ٳɹ�
void WindowDelegate::OnWindowDestroyed(CefRefPtr<CefWindow> window) {
    browser_view_ = nullptr;
    CefQuitMessageLoop();
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
