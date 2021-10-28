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
        std::string msgName = message->GetName();
        std::string filter = Helper::getFilter(message);
        json result;
        result["success"] = true;
        json configObj = Helper::getConfig(message);
        if (filter == "create")
        {
            auto iconPath = configObj["iconPath"].get<std::string>();
            wxString tip = wxEmptyString;
            if (!configObj["tip"].is_null()) {
                std::string temp = configObj["tip"].get<std::string>();
                tip = wxString::FromUTF8(temp);
            }
            Tray::taskBarIcon = new wxTaskBarIcon();
            ClientData* userData = new ClientData();
            userData->frame = frame;
            userData->msgName = message->GetName().ToString();
            Tray::taskBarIcon->SetClientObject(userData);
            wxIconLocation location;
            location.SetFileName(wxString::FromUTF8(iconPath));
            wxIcon icon(location);
            Tray::taskBarIcon->SetIcon(icon, tip);
            Tray::taskBarIcon->Bind(wxEVT_TASKBAR_MOVE, &onTrayEvent);
            Tray::taskBarIcon->Bind(wxEVT_TASKBAR_LEFT_DOWN, &onTrayEvent);
            Tray::taskBarIcon->Bind(wxEVT_TASKBAR_LEFT_DCLICK, &onTrayEvent);
            Tray::taskBarIcon->Bind(wxEVT_TASKBAR_LEFT_UP, &onTrayEvent);
            Tray::taskBarIcon->Bind(wxEVT_TASKBAR_RIGHT_DOWN, &onTrayEvent);
            Tray::taskBarIcon->Bind(wxEVT_TASKBAR_RIGHT_DCLICK, &onTrayEvent);
            Tray::taskBarIcon->Bind(wxEVT_TASKBAR_RIGHT_UP, &onTrayEvent);
            if (!configObj["menu"].is_null()){
                Tray::menu = new wxMenu();
                Tray::menu->SetClientObject(userData);
                int menuId = 0;
                for (auto& menuItem : configObj["menu"])
                {
                    auto name = menuItem["name"].get<std::string>();
                    Tray::menu->Append(menuId, wxString::FromUTF8(name));
                    wxTheApp->Bind(wxEVT_MENU, &onMenuClicked, menuId);
                    menuId += 1;
                }
            }
        }
        else if (filter == "resetIcon") {
            auto iconPath = configObj["iconPath"].get<std::string>();
            wxString tip = wxEmptyString;
            if (!configObj["tip"].is_null()) {
                std::string temp = configObj["tip"].get<std::string>();
                tip = wxString::FromUTF8(temp);
            }
            wxIconLocation location;
            location.SetFileName(wxString::FromUTF8(iconPath));
            wxIcon icon(location);
            Tray::taskBarIcon->SetIcon(icon, tip);
        }
        else if (filter == "destroy") {
            if (Tray::menu != nullptr) {
                delete Tray::menu;
                Tray::menu = nullptr;
            }
            if (Tray::taskBarIcon != nullptr) {
                Tray::taskBarIcon->RemoveIcon();
                Tray::taskBarIcon->Destroy();
                Tray::taskBarIcon = nullptr;
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
    static wxTaskBarIcon* taskBarIcon;
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
wxTaskBarIcon* Tray::taskBarIcon = nullptr;