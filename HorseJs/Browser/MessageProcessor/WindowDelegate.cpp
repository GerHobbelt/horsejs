#include "WindowDelegate.h"
#include "include/cef_app.h"
#include "include/views/cef_display.h"
#include "include/views/cef_box_layout.h"
#include "include/views/cef_fill_layout.h"
#include "include/views/cef_layout.h"
#include "PageHandler.h"
#include "../WebSocketClient.h"
#include "../ButtonDelegate.h"
#include "../MessageRouter/WindowRouter.h"
#include "../MessageRouter/ViewRouter.h"


WindowDelegate::WindowDelegate(const nlohmann::json& config, const int id):config(config),id(id) {
    auto url = config["url"].get<std::string>();
    view = ViewRouter::getInstance()->createView(url);
    CefWindow::CreateTopLevelWindow(this);
}
/// <summary>
/// 窗口创建成功
/// </summary>
/// <param name="window"></param>
void WindowDelegate::OnWindowCreated(CefRefPtr<CefWindow> window) {
    window->SetID(id);
    window->AddChildView(view);
    if (config["show"].get<bool>()) {
        window->Show();
    }
    window->SetTitle(config["title"].get<std::string>());
    win = window;

    auto wsClient = WebSocketClient::getInstance();
    nlohmann::json backMsg = { 
        {"__msgId","windowCreated"},
        {"winId",id},
        {"viewId",view->GetID()},
    };
    //todo 好像释放不了？这个要验证一下
    std::string msgStr = backMsg.dump();
    wsClient->sendMessage(msgStr);
}
int WindowDelegate::AddOverlayView(const nlohmann::json& overlayViewConfig) {
    auto url = overlayViewConfig["url"].get<std::string>();
    auto overlayView = ViewRouter::getInstance()->createView(url);
    overlayViews.push_back(overlayView);
    auto panelCtrl = win->AddOverlayView(overlayView, CEF_DOCKING_MODE_CUSTOM);
    overlayController.push_back(panelCtrl);
    auto dockVal = { 
        overlayViewConfig["dockType"].get<int>(), 
        overlayViewConfig["a"].get<int>(), 
        overlayViewConfig["b"].get<int>(), 
        overlayViewConfig["c"].get<int>(), 
        overlayViewConfig["d"].get<int>() 
    };
    dockInsets.push_back(dockVal);

    auto wsClient = WebSocketClient::getInstance();
    nlohmann::json backMsg = {
        {"__msgId","viewOverlayCreated"},
        {"winId",id},
        {"viewId",overlayView->GetID()},
    };
    //todo 好像释放不了？这个要验证一下
    std::string msgStr = backMsg.dump();
    wsClient->sendMessage(msgStr);

    return overlayView->GetID();
}
void WindowDelegate::removeView(int id) {
    int index = -1;
    for (int i = 0; i < overlayViews.size(); i++) {
        if (overlayViews.at(i)->GetID() == id) {
            index = i;
            break;
        }
    }   
    overlayController.erase(overlayController.begin() + index);
    //overlayController.at(0)->Destroy();
    overlayViews.erase(overlayViews.begin() + index);
    dockInsets.erase(dockInsets.begin() + index);
    auto view = overlayViews.at(index);
    ViewRouter::getInstance()->_removeView(view->GetID());
    view->GetBrowser()->GetHost()->CloseBrowser(true);
}
//void WindowDelegate::OnChildViewChanged(CefRefPtr<CefView> view, bool added, CefRefPtr<CefView> child) {
//
//}
void WindowDelegate::OnLayoutChanged(CefRefPtr<CefView> _view, const CefRect& newBounds) {
    if (_view->GetID() != view->GetID()) return;
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
    ViewRouter::getInstance()->_removeView(view->GetID());
    for (auto v :overlayViews) {
        ViewRouter::getInstance()->_removeView(v->GetID());
        v->GetBrowser()->GetHost()->CloseBrowser(true);
    }
    view = nullptr;
    overlayViews.clear();
    overlayController.clear();
    dockInsets.clear();
    //从WindowRouter的容器里移除
    WindowRouter::getInstance()->removeWindow(this);
}
void WindowDelegate::centerAndSize(const nlohmann::json& config) {
    CefRect rect = this->win->GetBounds();
    if (config.contains("params")) {
        rect.width = config["params"]["width"].get<int>();
        rect.height = config["params"]["height"].get<int>();
    }
    CefRefPtr<CefDisplay> display = CefDisplay::GetPrimaryDisplay();
    CefRect displayRect = display->GetBounds();
    rect.x = (displayRect.width - rect.width) / 2;
    rect.y = (displayRect.height - rect.height) / 2;
    this->win->SetBounds(rect);
}
void WindowDelegate::positionAndSize(const nlohmann::json& config) {
    CefRect rect = this->win->GetBounds();
    auto param = config["params"];
    rect.x = param["x"].get<int>();
    rect.y = param["y"].get<int>();
    if (param.contains("width")) {
        rect.width = param["width"].get<int>();
    }
    if (param.contains("height")) {
        rect.height = param["height"].get<int>();
    }
    this->win->SetBounds(rect);
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
