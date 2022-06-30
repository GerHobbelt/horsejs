#pragma once
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/cef_version.h"
#include <wx/platinfo.h>
#include <wx/version.h> 
#include <wx/socket.h>
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include "../Handler.h"
#include "../ViewDelegate.h"
#include "Helper.h"
#include "ClientData.h"
#include "../../Common/SQLite/sqlite3.h"
#include "../../Common/json.hpp"
using nlohmann::json;

static int callback(void* userDataPtr, int argc, char** argv, char** azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    auto userData = (ClientData*)userDataPtr;
    json result;
    result["success"] = true;
    Helper::SendMsg(userData->frame, userData->msgName + "_data", result);
    return 0;
}

class Db
{
public:
    Db() = delete;
    static sqlite3* db;
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        std::string msgName = message->GetName();
        std::string filter = Helper::getFilter(message);
        json configObj = Helper::getConfig(message);
        json result;
        result["success"] = true;
        if (filter == "open")
        {
            wxString dbPath;
            if (configObj["dbPath"].is_null()) {
                auto appDataPath = wxStandardPaths::Get().GetUserConfigDir();
                json appConfig = Config::get();
                auto appName = appConfig["appName"].get<std::string>();
                auto dbFolderPath = appDataPath + L"/" + wxString::FromUTF8(appName);
                bool flag = wxDir::Exists(dbFolderPath);
                if(!flag) wxDir::Make(dbFolderPath);
                dbPath = dbFolderPath + L"/db.db";
            }
            else
            {
                auto dbPath = wxString::FromUTF8(configObj["dbPath"].get<std::string>());
            }
            int rc;
            rc = sqlite3_open(dbPath.ToUTF8(), &db);
        }
        else if (filter == "close")
        {
            sqlite3_close(db);
        }
        else if (filter == "execute")
        {
            std::string sqlStr = configObj["sql"].get<std::string>();
            const char* sql = sqlStr.c_str();
            ClientData* userData = new ClientData();
            userData->frame = frame;
            userData->msgName = msgName;
            char* zErrMsg = 0;
            int rc;
            //todo 不需要回调
            rc = sqlite3_exec(db, sql, callback, (void*)userData, &zErrMsg);
            if (rc != SQLITE_OK) {
                result["success"] = false;
                result["error"] = std::string(zErrMsg);
                sqlite3_free(zErrMsg);
            }
        }
        Helper::SendMsg(frame, msgName, result);
        return true;
    }
};
sqlite3* Db::db;