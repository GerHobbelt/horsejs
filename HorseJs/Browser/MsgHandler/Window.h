#pragma once
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "../Handler.h"
#include "../ViewDelegate.h"
#include "../../Common/json.hpp"
#include "Helper.h"
using nlohmann::json;
class Window
{
public:
    Window() = delete;
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        std::string msgName = message->GetName();
        json configObj = Helper::getConfig(message);
        json result;
        result["success"] = true;
        CefRefPtr<CefBrowserView> browserView = CefBrowserView::GetForBrowser(browser);
        CefRefPtr<CefWindow> window = browserView->GetWindow();
        std::string filter = Helper::getFilter(message);
        if (filter == "maximize")
        {
            window->Maximize();            
        }
        else if (filter == "minimize")
        {
            window->Minimize();
        }
        else if (filter == "restore")
        {
            window->Restore();
        }
        else if (filter == "close")
        {
            window->Close();
        }
        else if (filter == "center")
        {            
            window->CenterWindow(window->GetSize());
        }
        else if (filter == "hide")
        {
            window->Hide();
        }
        else if (filter == "show")
        {
            window->Show();
        }
        else if (filter == "resize")
        {
            CefSize size(configObj["width"], configObj["height"]);
            window->SetSize(size);
        }
        else if (filter == "open")
        {
            CefSize size(configObj["width"], configObj["height"]);            
            CefBrowserSettings browserSettings;
            std::string url = configObj["url"];
            auto frameless = !configObj["frame"];
            CefRefPtr<CefBrowserView> browserView = CefBrowserView::CreateBrowserView(Handler::GetInstance(), url, browserSettings, nullptr, nullptr, new ViewDelegate());
            auto window = CefWindow::CreateTopLevelWindow(new WindowDelegate(browserView,frameless));
            window->SetSize(size);
        }
        else if (filter == "openDevTool")
        {
            CefBrowserSettings browserSettings;
            CefWindowInfo windowInfo;
            browser->GetHost()->ShowDevTools(windowInfo, Handler::GetInstance(), browserSettings, CefPoint());
            //CreatePopupWindow(browser, true, CefPopupFeatures(), windowInfo, client, settings);
        }
        else if (filter == "closeDevTool")
        {
            browser->GetHost()->CloseDevTools();
        }
        Helper::SendMsg(frame, msgName, result);
        return true;
    }
};