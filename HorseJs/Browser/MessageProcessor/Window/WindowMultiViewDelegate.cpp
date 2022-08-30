#include "WindowMultiViewDelegate.h"
#include "include/cef_app.h"
#include "include/views/cef_display.h"
#include "include/views/cef_box_layout.h"
#include "include/views/cef_fill_layout.h"
#include "include/views/cef_layout.h"
#include "../PageHandler.h"
#include "../ViewDelegate.h"
//#include "../../WebSocketClient.h"


WindowMultiViewDelegate::WindowMultiViewDelegate(const nlohmann::json& config):config(config) {
    CefBrowserSettings settings;
    auto pageHandler = PageHandler::getInstance();
    auto viewDelegate = ViewDelegate::getInstance();
    for (auto& viewConfig : config["views"]) {
        auto url = viewConfig["url"].get<std::string>();
        auto view = CefBrowserView::CreateBrowserView(pageHandler, url, settings, nullptr, nullptr, viewDelegate);
        views.push_back(view);
    }
}

/// <summary>
/// 窗口创建成功
/// </summary>
/// <param name="window"></param>
void WindowMultiViewDelegate::OnWindowCreated(CefRefPtr<CefWindow> window) {
    auto layoutDirection = config["layoutDirection"].get<std::string>();
    CefBoxLayoutSettings layoutSettings;
    layoutSettings.horizontal = layoutDirection == "horizontal";
    auto layout = window->SetToBoxLayout(layoutSettings);
    for (int i = 0; i < views.size();i++) {
        auto v = views.at(i);
        window->AddChildView(v);
        auto flex = config["views"][i]["flex"].get<int>();
        layout->SetFlexForView(v, flex);
    }
    if (config["show"].get<bool>()) {
        window->Show();
    }    
    window->SetTitle(config["title"].get<std::string>());
}
/// <summary>
/// 窗口销毁成功
/// </summary>
/// <param name="window"></param>
void WindowMultiViewDelegate::OnWindowDestroyed(CefRefPtr<CefWindow> window) {
    for (auto view : views) {
        view = nullptr;
    }
}
/// <summary>
/// 设置窗口位置和大小
/// </summary>
/// <param name="window"></param>
/// <returns></returns>
CefRect WindowMultiViewDelegate::GetInitialBounds(CefRefPtr<CefWindow> window) {
    auto position = config["position"].get<std::string>();
    CefRect rect;
    auto width = config["width"].get<unsigned int>();
    auto height = config["height"].get<unsigned int>();
    if (position == "center") {
        CefRefPtr<CefDisplay> display = CefDisplay::GetPrimaryDisplay();
        CefRect displayRect = display->GetBounds();
        rect.x = (displayRect.width - width) / 2;
        rect.y = (displayRect.height - height) / 2;
        rect.width = width;
        rect.height = height;
    }
    else {
        auto x = config["x"].get<int>();
        auto y = config["y"].get<int>();
        rect.x = x;
        rect.y = y;
        rect.width = width;
        rect.height = height;
    }
    return rect;    
}
/// <summary>
/// 是否为无边框窗口
/// </summary>
/// <param name="window"></param>
/// <returns></returns>
bool WindowMultiViewDelegate::IsFrameless(CefRefPtr<CefWindow> window) {
    //todo 
    if (isDevTool) {
        return false;
    }
    return config["frameless"].get<bool>();
    return false;
}
/// <summary>
/// 页面是否阻止窗口关闭
/// </summary>
/// <param name="window"></param>
/// <returns></returns>
bool WindowMultiViewDelegate::CanClose(CefRefPtr<CefWindow> window) {
    bool result = true;
    for (auto view : views) {
        CefRefPtr<CefBrowser> browser = view->GetBrowser();
        if (browser) {
            result = browser->GetHost()->TryCloseBrowser();
            if (!result) {
                return false;
            }
        }
    }
    return true;
}
