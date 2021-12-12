#pragma once
#include <windows.h> 
#include <shellapi.h>
#include "include/wrapper/cef_message_router.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/base/cef_bind.h"
#include "include/wrapper/cef_closure_task.h"
class Shell
{
public:
    Shell() = delete;
    static void open(const std::wstring& target, const std::wstring& workingDir)
    {
        auto dir = workingDir.empty() ? nullptr : workingDir.c_str();
        auto openResult = ShellExecuteW(nullptr, L"open", target.c_str(), nullptr, dir, SW_SHOWNORMAL);
        auto result = reinterpret_cast<ULONG_PTR>(openResult);
        if (result <= 32) {

        }
    }
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        std::string message_name = message->GetName();
        message_name.erase(0, message_name.find_first_of('_') + 1);
        if (message_name._Starts_with("openExternal"))
        {
            CefRefPtr<CefListValue> args = message->GetArgumentList();
            auto configStr = args->GetString(0).ToString();
            auto configObj = json::parse(configStr);
            CefString targetTemp = configObj["target"].get<std::string>();
            CefString workingDirTemp = configObj["workingDir"].get<std::string>();
            const std::wstring target = L"\"" + targetTemp.ToWString() + L"\"";
            const std::wstring workingDir = workingDirTemp.ToWString();
            //CefPostTask(TID_UI, base::Bind(&open, target,workingDir));
        }
        else if (message_name._Starts_with("openFolder"))
        {
        }

        return true;
    }
};