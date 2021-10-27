#pragma once
#include "include/wrapper/cef_message_router.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "DialogCallback.h"
#include "../../Common/json.hpp"
#include "Helper.h"
using nlohmann::json;
class Dialog
{
public:
    Dialog() = delete;
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        std::string msgName = message->GetName();
        std::string filter = Helper::getFilter(message);
        json configObj = Helper::getConfig(message);
        std::vector<CefString> fileFilters;
        for (const std::string & var : configObj["filters"])
        {
            fileFilters.push_back(var);
        }
        CefRefPtr<CefRunFileDialogCallback> dcb = new DialogCallback(msgName, frame);
        CefBrowserHost::FileDialogMode mode;
        auto title = Helper::convertString( configObj["title"].get<std::string>());
        auto defaultPath = Helper::convertString(configObj["defaultPath"].get<std::string>());
        auto filterIndex = configObj["filterIndex"].get<int>();
        if (filter._Starts_with("openFile"))
        {
            mode = configObj["multiSelections"].get<bool>() ? FILE_DIALOG_OPEN_MULTIPLE : FILE_DIALOG_OPEN;
            browser->GetHost()->RunFileDialog(mode, title, defaultPath, fileFilters, filterIndex, dcb);
        }
        else if (filter._Starts_with("openFolder"))
        {
            mode = FILE_DIALOG_OPEN_FOLDER;
            browser->GetHost()->RunFileDialog(mode, title, defaultPath, fileFilters, filterIndex, dcb);
        }
        //todo 这里是阻塞的，担心会有问题
        return true;
    }
};