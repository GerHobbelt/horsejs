#pragma once
#include "include/wrapper/cef_message_router.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
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
        std::string message_name = message->GetName();
        message_name.erase(0, message_name.find_first_of('.') + 1);
        if (message_name == "maximize")
        {
            window->Maximize();            
        }
        else if (message_name == "minimize")
        {
            window->Minimize();
        }
        else if (message_name == "close")
        {
            window->Close();
        }
        else if (message_name == "restore")
        {
            window->Restore();
        }
        else if (message_name == "hide")
        {
            window->Hide();
        }
        else if (message_name == "show")
        {
            window->Show();
        }
        else if (message_name == "resize")
        {
            CefRefPtr<CefListValue> args = message->GetArgumentList();
            CefSize size(args->GetInt(0), args->GetInt(1));
            window->SetSize(size);
        }
        return true;
    }
};