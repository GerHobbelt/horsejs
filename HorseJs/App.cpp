#include "App.h"
#include "include/cef_browser.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"
#include "WindowDelegate.h"
#include "Config.h"
#include "PageHandler.h"
#include "ViewDelegate.h"
//CEF主进程上下文环境初始化成功
void App::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();
    auto clientUseBackendServiceOrCustomService = config["clientUseBackendServerOrCustomServer"].get<std::string>();
    std::string url;
    if (clientUseBackendServiceOrCustomService == "customServer") {
        url = config["clientCustomServer"].get<std::string>();
    }
    else
    {
        url = config["backendHttpServer"].get<std::string>();
    }
    if (url.find("?") == std::string::npos) {
        url += "?ws="+ config["backendWebSocketServer"].get<std::string>();
    }
    else {
        url += "&ws="+ config["backendWebSocketServer"].get<std::string>();
    }
    CefBrowserSettings settings;
    CefRefPtr<PageHandler> pageHandler(new PageHandler());
    CefRefPtr<ViewDelegate> viewDelegate(new ViewDelegate());
    CefRefPtr<CefBrowserView> browserView = CefBrowserView::CreateBrowserView(pageHandler, url, settings, nullptr, nullptr, viewDelegate);
    CefWindow::CreateTopLevelWindow(new WindowDelegate(browserView,false));
}
