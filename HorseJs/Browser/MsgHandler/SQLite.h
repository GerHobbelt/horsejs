#pragma once
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/cef_version.h"
#include <wx/platinfo.h>
#include <wx/version.h> 
#include <wx/socket.h>
#include "../Handler.h"
#include "../ViewDelegate.h"
#include "Helper.h"

#include "../../Common/json.hpp"
using nlohmann::json;
class SQLite
{
public:
    SQLite() = delete;
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        std::string msgName = message->GetName();
        std::string filter = Helper::getFilter(message);
        json result;
        json data;
        result["success"] = true;
        if (filter == "open")
        {
            data = Config::get();
        }
        else if (filter == "close")
        {
            data["HorseJsVersion"] = { 0,0,7 };
            data["wxWidgetsVersion"] = { wxMAJOR_VERSION ,wxMINOR_VERSION ,wxRELEASE_NUMBER };
            data["cefVersion"] = { CEF_VERSION_MAJOR ,CEF_VERSION_MINOR ,CEF_VERSION_PATCH ,CEF_COMMIT_NUMBER };
            data["chromeVersion"] = { CHROME_VERSION_MAJOR ,CHROME_VERSION_MINOR ,CHROME_VERSION_BUILD ,CHROME_VERSION_PATCH };
        }
        else if (filter == "execute")
        {
            wxPlatformInfo platformInfo = wxPlatformInfo::Get();
            data["arch"] = platformInfo.GetArchName();
            data["name"] = platformInfo.GetOperatingSystemFamilyName();
            //data["name2"] = platformInfo.GetOperatingSystemIdName();
            data["version"] = { platformInfo.GetOSMajorVersion(), platformInfo.GetToolkitMinorVersion() ,platformInfo.GetOSMicroVersion() };

        }
        result["data"] = data;
        Helper::SendMsg(frame, msgName, result);
        return true;
    }
};