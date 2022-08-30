#pragma once
#include "include/wrapper/cef_message_router.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "DialogCallback.h"
#include "../../Common/json.hpp"
using nlohmann::json;
class Dialog
{
public:
    Dialog() = delete;
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        std::string message_name = message->GetName();
        message_name.erase(0, message_name.find_first_of('_') + 1);
        CefRefPtr<CefListValue> args = message->GetArgumentList();
        auto configStr = args->GetString(0).ToString();
        auto config = json::parse(configStr);
        std::vector<CefString> filter;
        for (const std::string & var : config["filters"])
        {
            filter.push_back(var);
        }
        CefRefPtr<CefRunFileDialogCallback> dcb = new DialogCallback(message, frame);
        CefBrowserHost::FileDialogMode mode;
        if (message_name._Starts_with("openFile"))
        {
            mode = config["multiSelections"].get<bool>() ? FILE_DIALOG_OPEN_MULTIPLE : FILE_DIALOG_OPEN;            
            browser->GetHost()->RunFileDialog(mode, config["title"].get<std::string>(), config["defaultFilePath"].get<std::string>(),filter, args->GetInt(3), dcb);
        }
        else if (message_name._Starts_with("openFolder"))
        {
            mode = FILE_DIALOG_OPEN_FOLDER;
            browser->GetHost()->RunFileDialog(mode, config["title"].get<std::string>(), config["defaultFilePath"].get<std::string>(), filter, args->GetInt(3), dcb);
        }
        return true;
    }
};