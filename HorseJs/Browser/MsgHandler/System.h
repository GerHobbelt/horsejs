#pragma once
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "../Handler.h"
#include "../ViewDelegate.h"
#include <windows.h>
#include <KnownFolders.h>
#include <shlobj.h>
#include <wx/wx.h>
#include <wx/msw/registry.h>
#include <wx/stdpaths.h>
#include <wx/notifmsg.h>

#include "../../Common/json.hpp"
#include "../../Common/Config.h"
#include "ClientData.h"
using nlohmann::json;
class System
{
public:
    System() = delete;
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        std::string msgName = message->GetName();
        std::string filter = Helper::getFilter(message);
        json result;
        result["success"] = true;
        json configObj = Helper::getConfig(message);
        if (filter._Starts_with("autoStart"))
        {
#if defined(OS_WIN)
            wxRegKey regKey(wxRegKey::HKCU, "Software\\Microsoft\\Windows\\CurrentVersion\\Run");
            auto appName = "horse.app." + Config::get()["appName"].get<std::string>();
            auto setOrRemove = configObj["setOrRemove"].get<std::string>();
            if (setOrRemove == "set")
            {
                bool flag = regKey.SetValue(appName, wxStandardPaths::Get().GetExecutablePath());
            }
            else if (setOrRemove == "remove")
            {
                regKey.DeleteValue(appName);
            }
#endif
        }
        else if (filter._Starts_with("protocolClient"))
        {
#if defined(OS_WIN)
            auto setOrRemove = configObj["setOrRemove"].get<std::string>();
            auto protocolName = configObj["protocolName"].get<std::string>();
            wxRegKey regKey0(wxRegKey::HKCR, protocolName + "\\shell\\open\\command");
            wxRegKey regKey(wxRegKey::HKCU, "Software\\Classes\\" + protocolName + "\\shell\\open\\command");
            if (setOrRemove == "set")
            {
                regKey0.Create();
                regKey.Create();
                auto val = "\"" + wxStandardPaths::Get().GetExecutablePath() + "\" --protocol-launcher \"%1\"";
                bool flag0 = regKey0.SetValue("", val);
                bool flag = regKey.SetValue("", val);
            }
            else
            {
                regKey0.DeleteSelf();
                regKey.DeleteSelf();
            }
#endif
        }
        else if (filter._Starts_with("notify"))
        {
            auto title = configObj["title"].get<std::string>();
            auto body = configObj["body"].get<std::string>();
            wxNotificationMessage* notification = new wxNotificationMessage(wxString::FromUTF8(title), wxString::FromUTF8(body));
            ClientData* clientData = new ClientData();
            clientData->frame = frame;
            clientData->msgName = message->GetName().ToString()+"_event";
            notification->Bind(wxEVT_NOTIFICATION_MESSAGE_CLICK, &System::notifyClick,-1,-1,clientData);
            notification->Bind(wxEVT_NOTIFICATION_MESSAGE_DISMISSED, &System::notifyClick, -1, -1, clientData);   //显示之前也会触发这个事件，奇怪
            notification->Show();
        }
        if (filter._Starts_with("openExternal"))
        {
            std::string targetTemp = configObj["target"].get<std::string>();
            wxLaunchDefaultApplication(wxString::FromUTF8(targetTemp));
        }
        Helper::SendMsg(frame, msgName, result);
        return true;
    };
    static void notifyClick(wxCommandEvent& event) {
        auto type = event.GetEventType();
        auto obj = static_cast<ClientData*>(event.GetEventUserData());
        if (!obj->isUsed && type == wxEVT_NOTIFICATION_MESSAGE_DISMISSED) {
            obj->isUsed = true;
            return;
        }
        json result;
        if (type == wxEVT_NOTIFICATION_MESSAGE_CLICK) {
            result["type"] = "click";
        }
        else if (type == wxEVT_NOTIFICATION_MESSAGE_DISMISSED) {
            result["type"] = "dismiss";
        }
        Helper::SendMsg(obj->frame, obj->msgName, result);
    };
};