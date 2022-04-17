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
    
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message,Handler* instance)
    {
        std::string msgName = message->GetName();
        std::string filter = Helper::getFilter(message);
        json result;
        result["success"] = true;
        json configObj = Helper::getConfig(message);
        if (filter._Starts_with("popup"))
        {
            instance->menuData = configObj["data"];
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
            for (auto& menuItem : configObj["data"])
            {
                auto name = menuItem["name"].get<std::string>();
                menu->Append(menuId, wxString::FromUTF8(name));
                wxTheApp->Bind(wxEVT_MENU, &onMenuClicked, menuId);
                menuId += 1;
            }
            auto win = wxWindow::FindFocus();
            Helper::SendMsg(frame, msgName, result);
            win->PopupMenu(menu,point);  //这里会阻塞，所以提前返回消息
            return true;
        }
        Helper::SendMsg(frame, msgName, result);
        return true;
    }
    static void onMenuClicked(wxCommandEvent& e) {
        auto id = e.GetId();
        auto target = wxDynamicCast(e.GetEventObject(),wxMenu);
        auto obj = static_cast<ClientData*>(target->GetClientObject());
        json result;
        result["index"] = id;
        Helper::SendMsg(obj->frame, obj->msgName, result);
    }
};