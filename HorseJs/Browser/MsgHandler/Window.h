#pragma once
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "../Handler.h"
#include "../ViewDelegate.h"
#include "../../Common/json.hpp"
using nlohmann::json;
class Window
{
public:
    Window() = delete;
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        CefRefPtr<CefBrowserView> browser_view = CefBrowserView::GetForBrowser(browser);
        if (!browser_view) return false;
        CefRefPtr<CefWindow> window = browser_view->GetWindow();
        if (!window) return false;
        std::string filter = Helper::getFilter(message);
        if (filter._Starts_with("maximize"))
        {
            window->Maximize();            
        }
        else if (filter._Starts_with("minimize"))
        {
            window->Minimize();
        }
        else if (filter._Starts_with("restore"))
        {
            window->Restore();
        }
        else if (filter._Starts_with("close"))
        {
            window->Close();
        }
        else if (filter._Starts_with("hide"))
        {
            window->Hide();
        }
        else if (filter._Starts_with("show"))
        {
            window->Show();
        }
        else if (filter._Starts_with("resize"))
        {
            CefRefPtr<CefListValue> args = message->GetArgumentList();
            auto sizeStr = args->GetString(0).ToString();
            auto sizeObj = json::parse(sizeStr);
            CefSize size(sizeObj["width"], sizeObj["height"]);
            window->SetSize(size);
        }
        else if (filter._Starts_with("open"))
        {
            CEF_REQUIRE_UI_THREAD();
            CefRefPtr<CefListValue> args = message->GetArgumentList();
            auto configStr = args->GetString(0).ToString();
            auto configObj = json::parse(configStr);
            CefSize size(configObj["width"], configObj["height"]);            
            CefBrowserSettings browser_settings;
            std::string url = configObj["url"];
            CefRefPtr<CefBrowserView> browser_view = CefBrowserView::CreateBrowserView(Handler::GetInstance(), url, browser_settings, nullptr, nullptr, new ViewDelegate());
            auto window = CefWindow::CreateTopLevelWindow(new WindowDelegate(browser_view));
            window->SetSize(size);
        }
        return true;
    }
};