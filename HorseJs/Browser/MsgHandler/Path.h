#pragma once
#include "include/wrapper/cef_message_router.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "DialogCallback.h"
#include <wx/stdpaths.h>

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
                result["data"] = wxStandardPaths::Get().GetUserDir(wxStandardPaths::Dir_Desktop).ToUTF8();
            }
            else if (pathName == "music")
            {
                result["data"] = wxStandardPaths::Get().GetUserDir(wxStandardPaths::Dir_Music).ToUTF8();
            }
            else if (pathName == "documents")
            {
                result["data"] = wxStandardPaths::Get().GetUserDir(wxStandardPaths::Dir_Documents).ToUTF8();
            }
            else if (pathName == "videos")
            {
                result["data"] = wxStandardPaths::Get().GetUserDir(wxStandardPaths::Dir_Videos).ToUTF8();
            }
            else if (pathName == "downloads")
            {
                result["data"] = wxStandardPaths::Get().GetUserDir(wxStandardPaths::Dir_Downloads).ToUTF8();
            }
            else if (pathName == "pictures")
            {
                result["data"] = wxStandardPaths::Get().GetUserDir(wxStandardPaths::Dir_Pictures).ToUTF8();
            }
            else if (pathName == "appData")
            {
                result["data"] = wxStandardPaths::Get().GetUserConfigDir().ToUTF8();
            }
            else if (pathName == "exePath")
            {
                result["data"] = wxStandardPaths::Get().GetExecutablePath().ToUTF8();
            }
            else if (pathName == "temp")
            {
                result["data"] = wxStandardPaths::Get().GetTempDir().ToUTF8();
            }
        }
        CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(message->GetName());
        auto resultStr = result.dump();
        CefRefPtr<CefListValue> msgArgs = msg->GetArgumentList();
        msgArgs->SetString(0, resultStr);
        frame->SendProcessMessage(PID_RENDERER, msg);
        return true;
    };
};
