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
            if (!OpenClipboard(NULL)) {
                result["success"] = false;
                result["error"] = "OpenClipboard Error";
            }
            else if (dataTypeStr == "text")
            {
                if (!IsClipboardFormatAvailable(CF_TEXT)) {
                    result["success"] = false;
                    result["error"] = "IsClipboardFormatAvailable CF_TEXT Error";
                } else {
                    HANDLE hClip = GetClipboardData(CF_TEXT);
                    char* pBuf = (char*)GlobalLock(hClip);
                    GlobalUnlock(hClip);
                    CloseClipboard();
                    result["data"] = pBuf;
                }
            }
            else if(dataTypeStr == "file")
            {
                if (!IsClipboardFormatAvailable(CF_HDROP)) {
                    result["success"] = false;
                    result["error"] = "IsClipboardFormatAvailable CF_TEXT Error";
                } else {
                    HDROP hDrop = HDROP(GetClipboardData(CF_HDROP));
                    if (hDrop != NULL)
                    {
                        WCHAR szFilePathName[MAX_PATH + 1] = { 0 };

                        UINT nNumOfFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0); 
                        for (UINT nIndex = 0; nIndex < nNumOfFiles; ++nIndex)
                        {
                            memset(szFilePathName, 0, MAX_PATH + 1);
                            DragQueryFile(hDrop, nIndex, szFilePathName, MAX_PATH);  // 得到文件名

                            _bstr_t path(szFilePathName);
                            std::string ss = (LPCSTR)path;

                            path_list.push_back(ss);
                        }
                    }
                    std::string data = (char*)GlobalLock(hClip);
                    GlobalUnlock(hClip);
                    CloseClipboard();
                    result["data"] = data;
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