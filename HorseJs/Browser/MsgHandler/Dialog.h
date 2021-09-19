#pragma once
#include "include/wrapper/cef_message_router.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
class Dialog
{
public:
    Dialog() = delete;
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        std::string message_name = message->GetName();
        message_name.erase(0, message_name.find_first_of('_') + 1);
        if (message_name == "maximize")
        {
            window->Maximize();            
        }
        else if (message_name == "minimize")
        {
            window->Minimize();
        }
        browser->GetHost()->RunFileDialog();
        return true;
    }
};