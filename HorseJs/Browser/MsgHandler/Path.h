#pragma once
#include "include/wrapper/cef_message_router.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include <wx/stdpaths.h>
#include "Helper.h"
#include "../../Common/json.hpp"
using nlohmann::json;
class Path
{
public:
    Path() = delete;
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        std::string msgName = message->GetName();
        std::string filter = Helper::getFilter(message);
        json result;
        result["success"] = true;
        json configObj = Helper::getConfig(message);
        if (filter == "readDir")
        {
            auto folderPath = Helper::convertString(configObj["path"].get<std::string>());
            result["data"] = json::array();
            for (auto& itr : std::filesystem::directory_iterator(folderPath))
            {
                auto pathStr = itr.path().wstring();
                result["data"].push_back(Helper::convertString(pathStr));
            }
        }else if (filter == "getPath")
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
        else if (filter == "isFolder")
        {
            auto path = Helper::convertString(configObj["path"].get<std::string>());
            auto flag = std::filesystem::is_directory(path);
            result["data"] = flag;
        }
        Helper::SendMsg(frame, msgName, result);
        return true;
    };
};
