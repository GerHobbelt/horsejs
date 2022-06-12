#pragma once
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "../../Common/json.hpp"
#include "Helper.h"
using nlohmann::json;
class Plugin
{
public:
    Plugin() = delete;
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        std::string msgName = message->GetName();
        std::string filter = Helper::getFilter(message);
        json result;
        result["success"] = true;
        json configObj = Helper::getConfig(message);
        if (filter == "autoStart")
        {
        }
        else if (filter == "notify")
        {
        }
        Helper::SendMsg(frame, msgName, result);
        return true;
    };
};
