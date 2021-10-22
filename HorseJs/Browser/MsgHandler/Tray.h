#pragma once
#include "include/wrapper/cef_message_router.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include <windowsx.h>
#include <wx/wx.h>
#include <wx/window.h>
#include <wx/menu.h>
#include <wx/event.h>
#include <wx/utils.h>
#include <wx/taskbar.h>
#include <wx/icon.h>

#include "../../Common/json.hpp"
#include "ClientData.h"
using nlohmann::json;
class Tray
{
public:
    Tray() = delete;

    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message, Handler* instance)
    {
        std::string message_name = message->GetName();
        message_name.erase(0, message_name.find_first_of('_') + 1);
        json result;
        result["success"] = true;
        CefRefPtr<CefListValue> args = message->GetArgumentList();
        auto configStr = args->GetString(0).ToString();
        json config = json::parse(configStr);
        static wxTaskBarIcon* taskBarIcon;
        if (message_name._Starts_with("create"))
        {
            if (taskBarIcon != nullptr) {
                taskBarIcon->Destroy();
            }
            auto iconPath = config["iconPath"].get<std::string>();
            auto tip = config["tip"].get<std::string>();
            taskBarIcon = new wxTaskBarIcon();
            wxIconLocation location;
            location.SetFileName(wxString::FromUTF8(iconPath));
            wxIcon icon(location);
            taskBarIcon->SetIcon(icon, wxString::FromUTF8(tip));
        }
        else if (message_name._Starts_with("reset")) {

        }
        else if (message_name._Starts_with("destroy")) {
            if (taskBarIcon != nullptr) {
                taskBarIcon->Destroy();
            }
        }
        CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(message->GetName());
        CefRefPtr<CefListValue> msgArgs = msg->GetArgumentList();
        msgArgs->SetSize(1);
        msgArgs->SetString(0, result.dump());
        frame->SendProcessMessage(PID_RENDERER, msg);
        return true;
    }
private:
    
};