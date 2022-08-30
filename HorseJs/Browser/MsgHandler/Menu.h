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
#include "ClientData.h"
#include "Helper.h"

using nlohmann::json;
class Menu
{
public:
    Menu() = delete;

    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        std::string msgName = message->GetName();
        std::string filter = Helper::getFilter(message);
        json result;
        result["success"] = true;
        json configObj = Helper::getConfig(message);
        if (filter == "popup")
        {
            wxPoint point = wxDefaultPosition;
            if (configObj["position"]["x"].get<int>() != -1) {
                point.x = configObj["position"]["x"].get<int>();
                point.y = configObj["position"]["y"].get<int>();
            }
            int menuId = 0;
            wxMenu* menu = new wxMenu();  //todo 需要释放吗
            ClientData* userData = new ClientData();
            userData->frame = frame;
            userData->msgName = msgName + "_event";
            menu->SetClientObject(userData);
            auto win = wxWindow::FindFocus();
            Menu::prepareMenu(menu, configObj["data"]);
            //for (auto& menuItem : configObj["data"])
            //{
            //    auto name = menuItem["name"].get<std::string>();
            //    menu->Append(menuId, wxString::FromUTF8(name));
            //    win->Bind(wxEVT_MENU, &Menu::onMenuClicked, menuId);
            //    menuId += 1;
            //}
            Helper::SendMsg(frame, msgName, result);
            win->PopupMenu(menu, point);  //这里会阻塞，所以提前返回消息
            return true;
        }
        Helper::SendMsg(frame, msgName, result);
        return true;
    }
    static void prepareMenu(wxMenu* menu,json& data) {
        for (auto& menuItem : data)
        {
            auto name = menuItem["name"].get<std::string>();
            auto menuId = menuItem["id"].get<int>();
            if (menuItem["subMenu"].is_array() && menuItem["subMenu"].size()>0) {
                wxMenu* subMenu = new wxMenu();
                subMenu->SetClientObject(menu->GetClientObject());
                menu->Append(menuId, wxString::FromUTF8(name),subMenu);
                prepareMenu(subMenu, menuItem["subMenu"]);
            }
            else
            {
                menu->Append(menuId, wxString::FromUTF8(name));
                wxTheApp->Bind(wxEVT_MENU, &Menu::onMenuClicked, menuId);
            }
        }
    }
    static void onMenuClicked(wxCommandEvent& e) {
        auto id = e.GetId();
        auto target = wxDynamicCast(e.GetEventObject(), wxMenu);
        auto obj = static_cast<ClientData*>(target->GetClientObject());
        json result;
        result["id"] = id;
        Helper::SendMsg(obj->frame, obj->msgName, result);
    }
};