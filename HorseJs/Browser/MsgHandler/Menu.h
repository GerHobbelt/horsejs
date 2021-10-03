#pragma once
#include "include/wrapper/cef_message_router.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include <wx/wx.h>
#include <wx/window.h>
#include <wx/menu.h>
#include <wx/event.h>
#include "../../Common/json.hpp"
using nlohmann::json;
class Menu
{
public:
    Menu() = delete;
    
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        std::string message_name = message->GetName();
        message_name.erase(0, message_name.find_first_of('_') + 1);
        json result;
        result["success"] = true;
        CefRefPtr<CefListValue> args = message->GetArgumentList();
        auto configStr = args->GetString(0).ToString();
        auto config = json::parse(configStr);
        wxMenu* menu = new wxMenu();         
        if (message_name._Starts_with("popup"))
        {
            int menuId = 666;
            for (auto& menuItem : config["data"])
            {
                //todo 不支持子菜单
                menu->Append(menuId, menuItem["name"].get<std::string>(), menuItem["tip"].get<std::string>());
                wxTheApp->Bind(wxEVT_MENU, &onMenuClicked, menuId);
                menuId += 1;
            }
            wxTheApp->GetTopWindow()->PopupMenu(menu);


            /*var element = document.getElementById("yourElement");
            var ev1 = new MouseEvent("mousedown", {
                bubbles: true,
                cancelable : false,
                view : window,
                button : 2,
                buttons : 2,
                clientX : element.getBoundingClientRect().x,
                clientY : element.getBoundingClientRect().y
                });
            element.dispatchEvent(ev1);
            var ev2 = new MouseEvent("mouseup", {
                bubbles: true,
                cancelable : false,
                view : window,
                button : 2,
                buttons : 0,
                clientX : element.getBoundingClientRect().x,
                clientY : element.getBoundingClientRect().y
                });
            element.dispatchEvent(ev2);
            var ev3 = new MouseEvent("contextmenu", {
                bubbles: true,
                cancelable : false,
                view : window,
                button : 2,
                buttons : 0,
                clientX : element.getBoundingClientRect().x,
                clientY : element.getBoundingClientRect().y
                });
            element.dispatchEvent(ev3);*/
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