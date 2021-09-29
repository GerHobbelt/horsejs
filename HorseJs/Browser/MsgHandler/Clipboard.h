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
        auto configStr = args->GetString(0).ToString();
        auto configObj = json::parse(configStr);
        CefString dataTypeStr = configObj["dataType"].get<std::string>();
        if (!wxTheClipboard->Open())
        {
            result["success"] = false;
            result["error"] = "OpenClipboard Error";
        }
        else if (message_name._Starts_with("getData"))
        {
            if (dataTypeStr == "text")
            {
                if (!wxTheClipboard->IsSupported(wxDataFormat(wxDF_TEXT))) {
                    result["success"] = false;
                    result["error"] = u8"���а���û���ı�����";
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
                //if (!wxTheClipboard->IsSupported(wxDataFormat(wxDF_FILENAME))) {
                //    result["success"] = false;
                //    result["error"] = u8"���а���û���ļ�����";
                //}
                //else
                //{
                    wxFileDataObject data;
                    wxTheClipboard->GetData(data);
                    auto files = data.GetFilenames();
                    result["data"] = {};
                    for (wxString& file : files)
                    {
                        result["data"].push_back(file.utf8_string());
                    }
                //}
            }
            else if (dataTypeStr == "html")
            {
                wxHTMLDataObject data;
                wxTheClipboard->GetData(data);
                auto html = data.GetHTML();
                result["data"] = html.utf8_string();
            }
        }
        else if (message_name._Starts_with("setData"))
        {
            if (dataTypeStr == "text")
            {
                std::string dataStr = configObj["data"].get<std::string>();
                wxString str = wxString::FromUTF8(dataStr);
                wxTextDataObject* data = new wxTextDataObject(str);
                wxTheClipboard->SetData(data);
            }
            else if (dataTypeStr == "file")
            {
                std::vector<std::string> dataArr = configObj["data"].get<std::vector<std::string>>();
                wxFileDataObject* data = new wxFileDataObject();
                for (auto& filePath : dataArr) {
                    wxString str = wxString::FromUTF8(filePath);
                    data->AddFile(str);
                }
                wxTheClipboard->SetData(data);
            }
            else if (dataTypeStr == "html")
            {
                std::string dataStr = configObj["data"].get<std::string>();
                wxString str = wxString::FromUTF8(dataStr);
                wxHTMLDataObject* data = new wxHTMLDataObject(str);
                wxTheClipboard->SetData(data);
            }
        }
        wxTheClipboard->Close();
        CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(message->GetName());
        CefRefPtr<CefListValue> msgArgs = msg->GetArgumentList();
        msgArgs->SetSize(1);
        msgArgs->SetString(0, result.dump());
        frame->SendProcessMessage(PID_RENDERER, msg);
        return true;
    }
};