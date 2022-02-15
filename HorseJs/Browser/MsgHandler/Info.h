#pragma once
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include <wx/platinfo.h>
#include "../Handler.h"
#include "../ViewDelegate.h"

#include "../../Common/json.hpp"
using nlohmann::json;
class Info
{
public:
    Info() = delete;
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        std::string message_name = message->GetName();
        message_name.erase(0, message_name.find_first_of('_') + 1);
        json result;
        result["success"] = true;
        if (message_name._Starts_with("getAppInfo"))
        {
            result["data"] = Config::get();
        }
        else if (message_name._Starts_with("getHorseInfo"))
        {
            json data;
            data["HorseJsVersion"] = "0.0.3";
            result["data"] = data;
        }
        else if (message_name._Starts_with("getOSInfo"))
        {
            wxPlatformInfo platformInfo = wxPlatformInfo::Get();
            json data;
            data["arch"] = platformInfo.GetArchName();
            data["name"] = platformInfo.GetOperatingSystemFamilyName();
            data["version"] = { platformInfo.GetOSMajorVersion(), platformInfo.GetToolkitMinorVersion() ,platformInfo.GetOSMicroVersion() };
            result["data"] = data;
        }
        CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(message->GetName());
        CefRefPtr<CefListValue> msgArgs = msg->GetArgumentList();
        msgArgs->SetSize(1);
        msgArgs->SetString(0, result.dump());
        frame->SendProcessMessage(PID_RENDERER, msg);
        return true;
    }
};