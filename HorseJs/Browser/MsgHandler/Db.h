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
            prepareSql(result, sqlStr.c_str());
            //const char* sql = sqlStr.c_str();
            //ClientData* userData = new ClientData();
            //userData->frame = frame;
            //userData->msgName = msgName;
            //char* zErrMsg = 0;
            //int rc;
            ////todo 不需要回调
            //rc = sqlite3_exec(db, sql, Db::callback, (void*)userData, &zErrMsg);
            //if (rc != SQLITE_OK) {
            //    result["success"] = false;
            //    result["error"] = std::string(zErrMsg);
            //    sqlite3_free(zErrMsg);
            //}

        }
        Helper::SendMsg(frame, msgName, result);
        return true;
    }
    static void prepareSql(json& result, const char* sqlStr) {
        sqlite3_stmt* stmt = NULL; //todo 异步的做
        const char* zTail;
        auto prepareResult = sqlite3_prepare_v2(db, sqlStr, -1, &stmt, &zTail);
        if (prepareResult == SQLITE_OK) {
            auto stepResult = sqlite3_step(stmt);
            if (stepResult == SQLITE_ROW) {
                json data;
                prepareData(data, stmt);
                result["data"] = data;
            }
            else if (stepResult == SQLITE_ERROR)
            {
                result["success"] = false;
                const char* zErrMsg = sqlite3_errmsg(db);
                result["error"] = std::string(zErrMsg);
            }
        }
        else if (prepareResult == SQLITE_OK)
        {
            result["success"] = false;
            const char* zErrMsg = sqlite3_errmsg(db);
            result["error"] = std::string(zErrMsg);
        }
        sqlite3_finalize(stmt);
        if (strlen(zTail) != 0) {
            prepareSql(result, zTail);
        }
    }
    static void prepareData(json& data,sqlite3_stmt* stmt) {        
        json row;
        int columnCount = sqlite3_column_count(stmt);
        for (size_t i = 0; i < columnCount; i++)
        {
            std::string columnName = sqlite3_column_name(stmt, i);
            int type = sqlite3_column_type(stmt, i);
            if (type == SQLITE_INTEGER) {
                row[columnName] = sqlite3_column_int(stmt, i);
            }
            else if (type == SQLITE_FLOAT)
            {
                row[columnName] = sqlite3_column_double(stmt, i);
            }
            else if (type == SQLITE3_TEXT)
            {
                const unsigned char* val = sqlite3_column_text(stmt, i);
                row[columnName] = reinterpret_cast<const char*>(val);
            }
        }
        data.push_back(row);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            prepareData(data, stmt);
        }
    }
    static int callback(void* userDataPtr, int argc, char** argv, char** azColName) {

        json result;
        result["success"] = true;
        json data;
        int i;
        for (i = 0; i < argc; i++) {
            data[std::string(azColName[i])] = argv[i] ? argv[i] : "";
        }
        result["data"] = data;
        auto userData = (ClientData*)userDataPtr;
        Helper::SendMsg(userData->frame, userData->msgName + "_data", result);
        return 0;
    }
};
sqlite3* Db::db;