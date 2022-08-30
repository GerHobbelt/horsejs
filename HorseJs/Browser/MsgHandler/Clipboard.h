#pragma once
#include "include/wrapper/cef_message_router.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "DialogCallback.h"
#include <wx/clipbrd.h>
#include "../../Common/json.hpp"
#include "Helper.h"
using nlohmann::json;
class Clipboard
{
public:
    Clipboard() = delete;
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        std::string msgName = message->GetName();
        std::string filter = Helper::getFilter(message);
        json result;
        result["success"] = true;
        json configObj = Helper::getConfig(message);
        CefString dataTypeStr = configObj["dataType"].get<std::string>();
        if (!wxTheClipboard->Open())
        {
            result["success"] = false;
            result["error"] = u8"剪切板打开失败";
            Helper::SendMsg(frame, msgName, result);
            return true;
        }
        if (filter == "getData")
        {
            if (dataTypeStr == "text")
            {
                if (!wxTheClipboard->IsSupported(wxDataFormat(wxDF_TEXT))) {
                    result["success"] = false;
                    result["error"] = u8"剪切板内没有文本数据";
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
                //    result["error"] = u8"剪切板内没有文件数据";
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
        else if (filter == "setData")
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
        Helper::SendMsg(frame, msgName, result);
        return true;
    }
};