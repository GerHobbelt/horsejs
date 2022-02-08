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
using nlohmann::json;
class System
{
public:
    System() = delete;
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        std::string message_name = message->GetName();
        message_name.erase(0, message_name.find_first_of('_') + 1);
        json result;
        result["success"] = true;
        CefRefPtr<CefListValue> args = message->GetArgumentList();
        auto configStr = args->GetString(0).ToString();
        auto configObj = json::parse(configStr);
        if (message_name._Starts_with("autoStart"))
        {
            #if defined(OS_WIN)
            wxRegKey regKey(wxRegKey::HKCU, "Software\\Microsoft\\Windows\\CurrentVersion\\Run");
            auto appName = "horse.app." + Config::get()["appName"].get<std::string>();
            auto setOrRemove = configObj["setOrRemove"].get<std::string>();
            if (setOrRemove == "set")
            {                           
                bool flag = regKey.SetValue(appName, wxStandardPaths::Get().GetExecutablePath());
            }
            else if(setOrRemove == "remove")
            {
                regKey.DeleteValue(appName);
            }
            #endif
        }
        else if (message_name._Starts_with("protocolClient"))
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
        else if (message_name._Starts_with("getHorseInfo"))
        {
            #if defined(OS_WIN)
            auto appName = "horse.app." + Config::get()["appName"].get<std::string>();
            wxRegKey regKey(wxRegKey::HKCU, "Software\\Classes\\"+appName+"\\shell\\open\\command");
            auto setOrRemove = configObj["setOrRemove"].get<std::string>();
            #endif
        }
        else if (message_name._Starts_with("notify"))
        {
            auto title = configObj["title"].get<std::string>();
            auto body = configObj["body"].get<std::string>();
            auto notification = wxNotificationMessage(title, body);
            notification.Show();
        }
        CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(message->GetName());
        CefRefPtr<CefListValue> msgArgs = msg->GetArgumentList();
        msgArgs->SetSize(1);
        msgArgs->SetString(0, result.dump());
        frame->SendProcessMessage(PID_RENDERER, msg);
        return true;
    }
};