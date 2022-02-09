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
#include "../../Common/json.hpp"
using nlohmann::json;
class Menu
{
public:
    Menu() = delete;
    
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message,Handler* instance)
    {
        std::string message_name = message->GetName();
        message_name.erase(0, message_name.find_first_of('_') + 1);
        json result;
        result["success"] = true;
        CefRefPtr<CefListValue> args = message->GetArgumentList();
        auto configStr = args->GetString(0).ToString();
        json config = json::parse(configStr);        
        if (message_name._Starts_with("popup"))
        {
            instance->menuData = config["data"];
            CefMouseEvent event;
            event.modifiers = cef_event_flags_t::EVENTFLAG_RIGHT_MOUSE_BUTTON;
            wxPoint point = wxDefaultPosition;
            if (config["position"]["x"].get<int>() != -1) {
                point.x = config["position"]["x"].get<int>();
                point.y = config["position"]["y"].get<int>();
            }
            int menuId = 666;
            wxMenu* menu = new wxMenu();
            for (auto& menuItem : config["data"])
            {
                auto name = menuItem["name"].get<std::string>();
                menu->Append(menuId, wxString::FromUTF8(name));
                //wxTheApp->Bind(wxEVT_MENU, &onMenuClicked, menuId);
                menuId += 1;
            }
            auto win = wxWindow::FindFocus();
            win->PopupMenu(menu,point);
        }
        else if (message_name._Starts_with("getHorseInfo"))
        {
            json data;
            data["HorseJsVersion"] = "0.0.1";
            result["data"] = data;
        }
        CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(message->GetName());
        CefRefPtr<CefListValue> msgArgs = msg->GetArgumentList();
        msgArgs->SetSize(1);
        msgArgs->SetString(0, result.dump());
        frame->SendProcessMessage(PID_RENDERER, msg);
        return true;
    }
    static void onMenuClicked(wxCommandEvent& e) {

    }
};