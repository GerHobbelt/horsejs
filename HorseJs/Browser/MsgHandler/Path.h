#pragma once
#include "include/wrapper/cef_message_router.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "DialogCallback.h"
#include <fstream>
#include <filesystem>
#include <codecvt>
#include <windows.h>
#include <KnownFolders.h>
#include <shlobj.h>
#include "../../Common/json.hpp"
using nlohmann::json;
class Path
{
public:
    Path() = delete;
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        std::string message_name = message->GetName();
        message_name.erase(0, message_name.find_first_of('_') + 1);
        CefRefPtr<CefListValue> args = message->GetArgumentList();
        json result;
        result["success"] = true;
        auto configStr = args->GetString(0).ToString();
        auto configObj = json::parse(configStr);
        if (message_name._Starts_with("readDir"))
        {
            static std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
            std::string folderPath = configObj["path"].get<std::string>();
            result["data"] = json::array();
            for (auto& itr : std::filesystem::directory_iterator(folderPath))
            {
                auto pathStr = itr.path().wstring();
                result["data"].push_back(utf8_conv.to_bytes(pathStr));
            }
        }else if (message_name._Starts_with("getPath"))
        {
            CefRefPtr<CefListValue> args = message->GetArgumentList();
            auto configStr = args->GetString(0).ToString();
            auto config = json::parse(configStr);
            auto pathName = config["name"].get<std::string>();
            if (pathName == "desktop") {
                wchar_t pathBuffer[MAX_PATH];
                SHGetFolderPath(NULL, CSIDL_DESKTOPDIRECTORY, NULL, SHGFP_TYPE_CURRENT, pathBuffer);
                result["data"] = getSystemPath(pathBuffer);
            }
            else if (pathName == "appData")
            {
                wchar_t pathBuffer[MAX_PATH];
                SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, pathBuffer);
                result["data"] = getSystemPath(pathBuffer);
            }
            else if (pathName == "exePath")
            {
                wchar_t pathBuffer[MAX_PATH];
                GetModuleFileName(NULL, pathBuffer, MAX_PATH);
                result["data"] = getSystemPath(pathBuffer);
            }
            else if (pathName == "exeFolder")
            {
                result["data"] = std::filesystem::current_path().generic_string();
            }
        }
        CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(message->GetName());
        auto resultStr = result.dump();
        CefRefPtr<CefListValue> msgArgs = msg->GetArgumentList();
        msgArgs->SetString(0, resultStr);
        frame->SendProcessMessage(PID_RENDERER, msg);
        return true;
    };

    static char* getSystemPath(const wchar_t* pathBuffer) {
        int pSize = WideCharToMultiByte(CP_OEMCP, 0, pathBuffer, wcslen(pathBuffer), NULL, 0, NULL, NULL);
        char* pCStrKey = new char[pSize + 1];
        WideCharToMultiByte(CP_OEMCP, 0, pathBuffer, wcslen(pathBuffer), pCStrKey, pSize, NULL, NULL);
        pCStrKey[pSize] = '\0';
        return pCStrKey;
    };
};
