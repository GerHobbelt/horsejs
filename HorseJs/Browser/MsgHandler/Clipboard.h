#pragma once
#include "include/wrapper/cef_message_router.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "DialogCallback.h"
#include <wx/clipbrd.h>
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
            if (!wxTheClipboard->Open())
            {

                result["success"] = false;
                result["error"] = "OpenClipboard Error";
                wxTheClipboard->SetData(new wxTextDataObject("Some text"));
                wxTheClipboard->Close();
            }
            auto configStr = args->GetString(0).ToString();
            auto configObj = json::parse(configStr);
            CefString dataTypeStr = configObj["dataType"].get<std::string>();
            if (!wxTheClipboard->Open()) {
                result["success"] = false;
                result["error"] = "OpenClipboard Error";
            }
            else if (dataTypeStr == "text")
            {
                if (!wxTheClipboard->IsSupported(wxDataFormat(wxDF_TEXT))) {
                    result["success"] = false;
                    result["error"] = "剪切板内没有文本数据";
                }
                else
                {
                    wxTextDataObject data;
                    wxTheClipboard->GetData(data);
                    std::string text = data.GetText().utf8_string();
                    result["data"] = text;
                }
            }
            else if (dataTypeStr == "file")
            {
                if (!wxTheClipboard->IsSupported(wxDataFormat(wxDF_FILENAME))) {
                    result["success"] = false;
                    result["error"] = "剪切板内没有文件数据";
                }
                else
                {
                    wxFileDataObject data;
                    wxTheClipboard->GetData(data);
                    auto files = data.GetFilenames();
                    result["data"] = {};
                    for (wxString& file : files)
                    {
                        result["data"].push_back(file.utf8_string());
                    }
                }
            }
            //CF_BITMAP    
        }
        else if (message_name._Starts_with("setData"))
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