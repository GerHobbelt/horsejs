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
    view->SetID(66);
    win = CefWindow::CreateTopLevelWindow(this);
    //url = "https://www.cnblogs.com";
    //auto view2 = this->createView(url);
    //overlayViews.push_back(view2);
}
CefRefPtr<CefBrowserView> WindowDelegate::createView(std::string& url) {
    CefBrowserSettings settings;
    auto pageHandler = PageHandler::getInstance();
    auto view = CefBrowserView::CreateBrowserView(pageHandler, url, settings, nullptr, nullptr, this);
    return view;
}
/// <summary>
/// ���ڴ����ɹ�
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
    auto url = overlayViewConfig["url"].get<std::string>();
    auto overlayView = this->createView(url);
    overlayViews.push_back(overlayView);
    auto panelCtrl = win->AddOverlayView(overlayView, CEF_DOCKING_MODE_CUSTOM);
    auto dock = overlayViewConfig["dock"].get<bool>();
    auto top = overlayViewConfig["top"].get<int>();
    auto left = overlayViewConfig["left"].get<int>();
    if (dock) {
        this->hasDockView = true;
        auto bottom = overlayViewConfig["bottom"].get<int>();
        auto right = overlayViewConfig["right"].get<int>();
        dockInsets.push_back(CefInsets(top, left, bottom, right));
        overlayController.push_back(panelCtrl);
    }
    else {
        auto width = overlayViewConfig["width"].get<int>();
        auto height = overlayViewConfig["height"].get<int>();
        auto rect = CefRect(top, left, width, height);
        panelCtrl->SetBounds(rect);
        panelCtrl->SetVisible(true);
    }
}
void WindowDelegate::OnLayoutChanged(CefRefPtr<CefView> _view, const CefRect& newBounds) {
    //todo ���벻���Ǵ��߿򴰿�
    //Ҫ�޸�node.js�Ľӿ�
    if (_view->GetID() == 66 && hasDockView){
        auto winBounds = win->GetBounds();
        for (int i = 0; i < overlayController.size(); i++) {
            auto inset = dockInsets.at(i);
            auto ctrl = overlayController.at(i);
            auto viewBounds = CefRect(inset.left, inset.top, winBounds.width - inset.right-inset.left, winBounds.height - inset.bottom-inset.top);
            ctrl->SetBounds(viewBounds);
            ctrl->SetVisible(true);
        }
    }
}
/// <summary>
/// �������ٳɹ�
/// </summary>
/// <param name="window"></param>
void WindowDelegate::OnWindowDestroyed(CefRefPtr<CefWindow> window) {
    view = nullptr;
    overlayViews.clear();
}
/// <summary>
/// ���ô���λ�úʹ�С
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
/// �Ƿ�Ϊ�ޱ߿򴰿�
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
/// ҳ���Ƿ���ֹ���ڹر�
/// </summary>
/// <param name="window"></param>
/// <returns></returns>
bool WindowDelegate::CanClose(CefRefPtr<CefWindow> window) {
    CefRefPtr<CefBrowser> browser = view->GetBrowser();
    
    bool result = browser->GetHost()->TryCloseBrowser();
    return result;
}
/// <summary>
/// ��ǰҳ�浯���´���ʱ�˷�����ִ��
/// </summary>
/// <param name="browserView"></param>
/// <param name="popupBrowserView"></param>
/// <param name="isDevtools"></param>
/// <returns></returns>
bool WindowDelegate::OnPopupBrowserViewCreated(CefRefPtr<CefBrowserView> browserView, CefRefPtr<CefBrowserView> popupBrowserView, bool isDevtools)
{
    //todo isDevtoolsû����
    //todo window.open���Ĳ��������
    CefWindow::CreateTopLevelWindow(new WindowPopupDelegate(popupBrowserView));
    return true;
}
