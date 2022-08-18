#include "App.h"
#include "include/cef_browser.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"
#include "WindowDelegate.h"
//CEF�����������Ļ�����ʼ���ɹ�
void App::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();
    auto url = "https://sso.hikvision.com/login";
    CefBrowserSettings settings;
    CefRefPtr<CefBrowserView> browser_view = CefBrowserView::CreateBrowserView(nullptr, url, settings, nullptr, nullptr, nullptr);
    CefWindow::CreateTopLevelWindow(new WindowDelegate(browser_view));
}
