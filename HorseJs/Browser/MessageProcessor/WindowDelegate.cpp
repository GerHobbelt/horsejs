#include "WindowDelegate.h"
#include "include/cef_app.h"
#include "include/views/cef_display.h"
#include "include/views/cef_box_layout.h"
#include "include/views/cef_fill_layout.h"
#include "include/views/cef_layout.h"
#include "PageHandler.h"
#include "../WebSocketClient.h"
#include "./Window/WindowPopupDelegate.h"
#include "../ButtonDelegate.h"


WindowDelegate::WindowDelegate(const nlohmann::json& config):config(config) {
    auto url = config["url"].get<std::string>();
    view = this->createView(url);
    view->SetID(0);
    win = CefWindow::CreateTopLevelWindow(this);
}
CefRefPtr<CefBrowserView> WindowDelegate::createView(std::string& url) {
    CefBrowserSettings settings;
    auto pageHandler = PageHandler::getInstance();
    auto view = CefBrowserView::CreateBrowserView(pageHandler, url, settings, nullptr, nullptr, this);
    return view;
}
/// <summary>
/// 窗口创建成功
/// </summary>
/// <param name="window"></param>
void WindowDelegate::OnWindowCreated(CefRefPtr<CefWindow> window) {
    window->AddChildView(view);
    if (config["show"].get<bool>()) {
        window->Show();
    }
    window->SetTitle(config["title"].get<std::string>());
}
void WindowDelegate::AddOverlayView(const nlohmann::json& overlayViewConfig) {
    auto dockVal = { overlayViewConfig["dockType"].get<int>(), overlayViewConfig["a"].get<int>(), overlayViewConfig["b"].get<int>(), overlayViewConfig["c"].get<int>(), overlayViewConfig["d"].get<int>() };
    dockInsets.push_back(dockVal);
    auto url = overlayViewConfig["url"].get<std::string>();
    auto overlayView = this->createView(url);
    overlayViews.push_back(overlayView);
    auto panelCtrl = win->AddOverlayView(overlayView, CEF_DOCKING_MODE_CUSTOM);    
    overlayController.push_back(panelCtrl);
}
void WindowDelegate::OnLayoutChanged(CefRefPtr<CefView> _view, const CefRect& newBounds) {
    if (_view->GetID() != 0) return;
    //todo 必须不能是带边框窗口
    for (int i = 0; i < overlayController.size(); i++) {
        auto inset = dockInsets.at(i);
        auto ctrl = overlayController.at(i);
        CefRect viewBounds;
        switch (inset[0])
        {
            case 0: {
                viewBounds.x = inset.at(1); 
                viewBounds.y = inset.at(2); 
                viewBounds.width = inset.at(3); 
                viewBounds.height = inset.at(4);
                break;
            }
            case 1: {
                auto winBounds = win->GetBounds();
                viewBounds.x = inset.at(1);
                viewBounds.y = inset.at(2);
                viewBounds.width = winBounds.width - inset.at(3) - inset.at(1);
                viewBounds.height = inset.at(4);
                break;
            }
            case 2: {
                auto winBounds = win->GetBounds();
                viewBounds.x = inset.at(1);
                viewBounds.y = inset.at(2);
                viewBounds.width = inset.at(4);
                viewBounds.height = winBounds.height - inset.at(2) - inset.at(3);
                break;
            }
            case 3: {
                auto winBounds = win->GetBounds();
                viewBounds.x = winBounds.width - inset.at(1) - inset.at(3);
                viewBounds.y = winBounds.height - inset.at(2) - inset.at(4);
                viewBounds.width = inset.at(3);
                viewBounds.height = inset.at(4);
                break;
            }
            case 4: {
                auto winBounds = win->GetBounds();
                viewBounds.x = winBounds.width - inset.at(1) - inset.at(4);
                viewBounds.y = inset.at(3);
                viewBounds.width = inset.at(4);
                viewBounds.height = winBounds.height - inset.at(2) - inset.at(3);
                break;
            }
            case 5: {
                auto winBounds = win->GetBounds();
                viewBounds.x = inset.at(3);
                viewBounds.y = winBounds.height - inset.at(2) - inset.at(4);
                viewBounds.width = winBounds.width - inset.at(1) - inset.at(3);
                viewBounds.height = inset.at(4);
                break;
            }
            case 6: {
                auto winBounds = win->GetBounds();
                viewBounds.x = inset.at(1);
                viewBounds.y = inset.at(2);
                viewBounds.width = winBounds.width - inset.at(1) - inset.at(3);
                viewBounds.height = winBounds.height - inset.at(2) - inset.at(4);
                break;
            }
            default:
                break;
        }
        ctrl->SetBounds(viewBounds);
        ctrl->SetVisible(true);
    }
}
/// <summary>
/// 窗口销毁成功
/// </summary>
/// <param name="window"></param>
void WindowDelegate::OnWindowDestroyed(CefRefPtr<CefWindow> window) {
    view = nullptr;
    overlayViews.clear();
    overlayController.clear();
    dockInsets.clear();
}
/// <summary>
/// 设置窗口位置和大小
/// </summary>
/// <param name="window"></param>
/// <returns></returns>
CefRect WindowDelegate::GetInitialBounds(CefRefPtr<CefWindow> window) {
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
bool WindowDelegate::IsFrameless(CefRefPtr<CefWindow> window) {
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
bool WindowDelegate::CanClose(CefRefPtr<CefWindow> window) {
    CefRefPtr<CefBrowser> browser = view->GetBrowser();    
    bool result = browser->GetHost()->TryCloseBrowser();
    return result;
}
/// <summary>
/// 当前页面弹出新窗口时此方法被执行
/// </summary>
/// <param name="browserView"></param>
/// <param name="popupBrowserView"></param>
/// <param name="isDevtools"></param>
/// <returns></returns>
bool WindowDelegate::OnPopupBrowserViewCreated(CefRefPtr<CefBrowserView> browserView, CefRefPtr<CefBrowserView> popupBrowserView, bool isDevtools)
{
    //todo isDevtools没用上
    //todo window.open传的参数在哪里？
    CefWindow::CreateTopLevelWindow(new WindowPopupDelegate(popupBrowserView));
    return true;
}
