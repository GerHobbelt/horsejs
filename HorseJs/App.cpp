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
    auto configJson = Config::get();
    auto clientUseStaticFileOrHttpService = configJson["clientUseStaticFileOrHttpService"].get<std::string>();
    std::string url;
    if (clientUseStaticFileOrHttpService == "httpService") {
        url = configJson["clientHttpService"].get<std::string>();
    }
    else
    {
        url = "http://localhost:"+ configJson["backendPort"].get<std::string>();
    }    
    CefBrowserSettings settings;
    CefRefPtr<PageHandler> pageHandler(new PageHandler());
    CefRefPtr<ViewDelegate> viewDelegate(new ViewDelegate());
    CefRefPtr<CefBrowserView> browserView = CefBrowserView::CreateBrowserView(pageHandler, url, settings, nullptr, nullptr, viewDelegate);
    CefWindow::CreateTopLevelWindow(new WindowDelegate(browserView,false));
}
