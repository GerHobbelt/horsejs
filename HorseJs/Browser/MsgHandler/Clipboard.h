#pragma once
#include "include/wrapper/cef_message_router.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "DialogCallback.h"
#include "../../Common/json.hpp"
using nlohmann::json;
class Clipboard 
{
public:
    Clipboard() = delete;
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        std::string message_name = message->GetName();
        message_name.erase(0, message_name.find_first_of('_') + 1);
        CefRefPtr<CefListValue> args = message->GetArgumentList();
        json result;
        result["success"] = true;
        if (message_name._Starts_with("getData"))
        {
            
            auto configStr = args->GetString(0).ToString();
            auto configObj = json::parse(configStr);
            CefString dataTypeStr = configObj["dataType"].get<std::string>();
            int dataType = 1;
            if (dataTypeStr == "text") dataType = CF_TEXT;
            if (!OpenClipboard(NULL)) return true;
            if(!IsClipboardFormatAvailable(CF_TEXT)) return true;
            HANDLE hClip = GetClipboardData(CF_TEXT);
            char* pBuf = (char*)GlobalLock(hClip);
            GlobalUnlock(hClip);
            CloseClipboard();
            result["data"] = pBuf;
        }
        else if (message_name._Starts_with("getHtml"))
        {
        }
        else if (message_name._Starts_with("getHtml"))
        {
        }
        else if (message_name._Starts_with("getHtml"))
        {
        }
        CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(message->GetName());
        CefRefPtr<CefListValue> msgArgs = msg->GetArgumentList();
        msgArgs->SetSize(1);
        msgArgs->SetString(0, result.dump());
        frame->SendProcessMessage(PID_RENDERER, msg);
        return true;
    }
};