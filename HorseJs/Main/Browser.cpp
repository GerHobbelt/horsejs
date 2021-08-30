#include "Browser.h"
#include <string>
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"
#include "../Browser/ViewDelegate.h"
#include "../Browser/WindowDelegate.h"
#include "../Browser/Handler.h"

void Browser::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();
    CefRefPtr<Handler> handler(new Handler());
    CefBrowserSettings browser_settings;
    std::string url = "horse://test/handler.html";
    CefRefPtr<CefBrowserView> browser_view = CefBrowserView::CreateBrowserView(handler, url, browser_settings, nullptr, nullptr, new ViewDelegate());
    CefWindow::CreateTopLevelWindow(new WindowDelegate(browser_view));
}

CefRefPtr<CefClient> Browser::GetDefaultClient() {
    return Handler::GetInstance();
}
