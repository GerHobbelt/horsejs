#include "WindowDelegate.h"
#include "include/cef_app.h"
#include "include/views/cef_display.h"
#include "Config.h"
//窗口创建成功
void WindowDelegate::OnWindowCreated(CefRefPtr<CefWindow> window) {
    window->AddChildView(browserView);
    window->Show();
    browserView->RequestFocus();
    window->SetTitle(L"这是我的窗口标题");
    //window->CenterWindow(CefSize(800, 600));
}
//窗口销毁成功
void WindowDelegate::OnWindowDestroyed(CefRefPtr<CefWindow> window) {
    browserView = nullptr;
    CefQuitMessageLoop();
}
//设置窗口位置和大小
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
    return Config::get()["framelessWindow"].get<bool>();
}
