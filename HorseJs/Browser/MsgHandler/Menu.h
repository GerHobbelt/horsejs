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
        wxMenu* menu = new wxMenu();         
        if (message_name._Starts_with("popup"))
        {
            int menuId = 666;
            instance->menuData = config["data"];
            HWND winId = browser->GetHost()->GetWindowHandle();
            //SendMessage(winId, WM_NCRBUTTONUP, 0, MAKELPARAM(300,300));
            CefMouseEvent event;
            event.modifiers = cef_event_flags_t::EVENTFLAG_RIGHT_MOUSE_BUTTON;
            if (config["position"]["x"].get<int>() == -1) {
                //LPPOINT lParam;
                //GetCursorPos(lParam);
                //int xPos = -GET_X_LPARAM(lParam);
                //int yPos = -GET_Y_LPARAM(lParam);
                wxPoint mousePoint = wxGetMousePosition();
                CefRefPtr<CefBrowserView> browser_view = CefBrowserView::GetForBrowser(browser);
                CefRefPtr<CefWindow> window = browser_view->GetWindow();
                CefRect rect = window->GetBounds();
                CefPoint point1(mousePoint.x, mousePoint.y);
                float scaleFactor = window->GetDisplay()->GetDeviceScaleFactor();
                CefPoint point2(mousePoint.x, mousePoint.y);
                window->GetDisplay()->ConvertPointFromPixels(point2);
                //LPRECT lpRect;
                //GetWindowRect(winId,lpRect);
                event.x = mousePoint.x - rect.x* scaleFactor - 128;
                event.y = mousePoint.y - rect.y* scaleFactor - 56; //todo 
            }
            else
            {
                event.x = config["position"]["x"].get<int>();
                event.y = config["position"]["y"].get<int>();
            }
            browser->GetHost()->SendMouseClickEvent(event, CefBrowserHost::MouseButtonType::MBT_RIGHT, true,1);
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