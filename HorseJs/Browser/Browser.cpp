#include "Browser.h"
#include <string>
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"
#include "ViewDelegate.h"
#include "WindowDelegate.h"
#include "Handler.h"
#include "../Common/Config.h"

void Browser::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();
    CefRefPtr<Handler> handler(new Handler());
    CefBrowserSettings browserSettings;
    //todo 考虑一下怎么做
    //browser_settings.javascript_access_clipboard = cef_state_t::STATE_ENABLED;
    //browser_settings.javascript_close_windows = cef_state_t::STATE_ENABLED;
    //browser_settings.javascript_dom_paste = cef_state_t::STATE_ENABLED;
    auto config = Config::get();
    auto url = config["startPath"].get<std::string>();
    if(!url._Starts_with("http")) url = "http://horse/"+ url;  //todo 这里不应该有app子目录
    CefRefPtr<CefBrowserView> browserView = CefBrowserView::CreateBrowserView(handler, url, browserSettings, nullptr, nullptr, new ViewDelegate());
    //browser_view->SetID(2);
    CefWindow::CreateTopLevelWindow(new WindowDelegate(browserView));
}

CefRefPtr<CefClient> Browser::GetDefaultClient() {
    return Handler::GetInstance();
}