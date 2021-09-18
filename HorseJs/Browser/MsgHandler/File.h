#pragma once
#include <fstream>
#include <filesystem>
#include <codecvt> // codecvt_utf8
#include <locale>  // wstring_convert
#include "include/wrapper/cef_message_router.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "DialogCallback.h"
#include "../../Common/json.hpp"
using nlohmann::json;
class File
{
public:
    File() = delete;
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        std::string message_name = message->GetName();
        message_name.erase(0, message_name.find_first_of('_') + 1);
        CefRefPtr<CefListValue> args = message->GetArgumentList();
        auto configStr = args->GetString(0).ToString();
        auto configObj = json::parse(configStr);
        json result;
        result["success"] = true;
        if (message_name._Starts_with("readDir"))
        {
            std::string folderPath = configObj["folderPath"].get<std::string>();
            result["data"] = json::array();
            static std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
            for (auto& itr : std::filesystem::directory_iterator(folderPath))
            {
                auto pathStr = itr.path().wstring();
                result["data"].push_back(utf8_conv.to_bytes(pathStr));
                //arr.push_back(pathStr);
                
                //if (std::filesystem::is_directory(itr.status()))
                //{
                //    FindFilesInFolder(itr.path().string(), vecFiles);
                //}
                //else
                //{
                //    //if (std::regex_match(filename.string(), fileSuffix))
                //    //std::filesystem::remove_all(version_dir, ec);
                //    //std::filesystem::copy_file(from_file, to_file, std::filesystem::copy_options::skip_existing, ec))
                //    vecFiles.push_back(itr.path().string());
                //}
            }
            //result["data"] = arr;
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
        auto resultStr = result.dump();
        msgArgs->SetSize(1);
        msgArgs->SetString(0, resultStr);
        frame->SendProcessMessage(PID_RENDERER, msg);
        return true;
    }
};