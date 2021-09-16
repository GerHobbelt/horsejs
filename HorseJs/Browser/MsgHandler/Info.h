#pragma once
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "../Handler.h"
#include "../ViewDelegate.h"
#include <windows.h>
#include <KnownFolders.h>
#include <shlobj.h>
#include "../../Common/json.hpp"
using nlohmann::json;
class Info
{
public:
    Info() = delete;
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        std::string message_name = message->GetName();
        message_name.erase(0, message_name.find_first_of('_') + 1);
        if (message_name._Starts_with("getPath"))
        {
            CefRefPtr<CefListValue> args = message->GetArgumentList();
            auto configStr = args->GetString(0).ToString();
            auto config = json::parse(configStr);
            auto pathName = config["name"].get<std::string>();
            json result;
            result["success"] = true;
            if (pathName == "desktop") {
                std::string data = getSystemPath();   
                result["data"] = data;
            }
            CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(message->GetName());
            CefRefPtr<CefListValue> msgArgs = msg->GetArgumentList();
            msgArgs->SetSize(1);
            msgArgs->SetString(0, result.dump());
            frame->SendProcessMessage(PID_RENDERER, msg);
        }
        else if (message_name._Starts_with("openFolder"))
        {
            //mode = FILE_DIALOG_OPEN_FOLDER;
        }
        return true;
    }
    static char* getSystemPath() {
        wchar_t system_buffer[MAX_PATH];
        SHGetFolderPath(NULL, CSIDL_DESKTOPDIRECTORY, NULL, SHGFP_TYPE_CURRENT, system_buffer);
        int pSize = WideCharToMultiByte(CP_OEMCP, 0, system_buffer, wcslen(system_buffer), NULL, 0, NULL, NULL);
        char* pCStrKey = new char[pSize + 1];
        WideCharToMultiByte(CP_OEMCP, 0, system_buffer, wcslen(system_buffer), pCStrKey, pSize, NULL, NULL);
        pCStrKey[pSize] = '\0';
        return pCStrKey;
    }
};