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
            ClientData* userData = new ClientData();
            userData->frame = frame;
            userData->msgName = message->GetName().ToString();
            taskBarIcon->SetClientObject(userData);
            wxIconLocation location;
            location.SetFileName(wxString::FromUTF8(iconPath));
            wxIcon icon(location);
            taskBarIcon->SetIcon(icon, wxString::FromUTF8(tip));
            taskBarIcon->Bind(wxEVT_TASKBAR_MOVE, &onTrayEvent);
            taskBarIcon->Bind(wxEVT_TASKBAR_LEFT_DOWN, &onTrayEvent);
            taskBarIcon->Bind(wxEVT_TASKBAR_LEFT_DCLICK, &onTrayEvent);
            taskBarIcon->Bind(wxEVT_TASKBAR_LEFT_UP, &onTrayEvent);
            taskBarIcon->Bind(wxEVT_TASKBAR_RIGHT_DOWN, &onTrayEvent);
            taskBarIcon->Bind(wxEVT_TASKBAR_RIGHT_DCLICK, &onTrayEvent);
            taskBarIcon->Bind(wxEVT_TASKBAR_RIGHT_UP, &onTrayEvent);
            if (!config["menu"].is_null()){
                Tray::menu = new wxMenu();
                Tray::menu->SetClientObject(userData);
                int menuId = 0;
                for (auto& menuItem : config["menu"])
                {
                    auto name = menuItem["name"].get<std::string>();
                    Tray::menu->Append(menuId, wxString::FromUTF8(name));
                    wxTheApp->Bind(wxEVT_MENU, &onMenuClicked, menuId);
                    menuId += 1;
                }
            }
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
    static wxMenu* menu;
    static void onMenuClicked(wxCommandEvent& e) {
        auto id = e.GetId();
        auto target = wxDynamicCast(e.GetEventObject(), wxMenu);
        auto obj = static_cast<ClientData*>(target->GetClientObject());
        CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(obj->msgName+"_menu");
        CefRefPtr<CefListValue> msgArgs = msg->GetArgumentList();
        json result;
        result["index"] = id;
        msgArgs->SetSize(1);
        msgArgs->SetString(0, result.dump());
        obj->frame->SendProcessMessage(PID_RENDERER, msg);
    }
    static void onTrayEvent(wxTaskBarIconEvent& e) {
        auto target = wxDynamicCast(e.GetEventObject(), wxTaskBarIcon);
        auto obj = static_cast<ClientData*>(target->GetClientObject());
        std::string clickType;
        if (e.GetEventType() == wxEVT_TASKBAR_MOVE) {
            clickType = "mouseMove";
        }
        else if(e.GetEventType() == wxEVT_TASKBAR_LEFT_DOWN) {
            clickType = "leftButtonDown";
        }
        else if (e.GetEventType() == wxEVT_TASKBAR_LEFT_DCLICK) {
            clickType = "leftButtonDoubleClick";
        }
        else if (e.GetEventType() == wxEVT_TASKBAR_LEFT_UP) {
            clickType = "leftButtonUp";
        }
        else if (e.GetEventType() == wxEVT_TASKBAR_RIGHT_DOWN) {
            clickType = "rightButtonDown";
        }
        else if (e.GetEventType() == wxEVT_TASKBAR_RIGHT_DCLICK) {
            clickType = "rightButtonDoubleClick";
        }
        else if (e.GetEventType() == wxEVT_TASKBAR_RIGHT_UP) {
            if (Tray::menu) {
                target->PopupMenu(menu);
            }            
            clickType = "rightButtonUp";
        }
        CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(obj->msgName+"_tray");
        CefRefPtr<CefListValue> msgArgs = msg->GetArgumentList();
        json result;
        result["clickType"] = clickType;
        msgArgs->SetSize(1);
        msgArgs->SetString(0, result.dump());
        obj->frame->SendProcessMessage(PID_RENDERER, msg);
    }
};
wxMenu*  Tray::menu = nullptr;