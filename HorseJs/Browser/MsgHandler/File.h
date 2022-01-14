#pragma once
#include <fstream>
#include <filesystem>
#include <codecvt> // codecvt_utf8
#include <locale>  // wstring_convert
#include <sstream>
#include "include/wrapper/cef_message_router.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/cef_task.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"
#include "include/base/cef_callback.h"
#include "wx/filefn.h"


#include "../../Common/json.hpp"
using nlohmann::json;
class File
{
public:
    File() = delete;
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        static std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
        std::string message_name = message->GetName();
        message_name.erase(0, message_name.find_first_of('_') + 1);
        CefRefPtr<CefListValue> args = message->GetArgumentList();
        auto configStr = args->GetString(0).ToString();
        auto configObj = json::parse(configStr);
        json result;
        result["success"] = true;
        CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(message->GetName());        
        if (message_name._Starts_with("getFileSize"))
        {
            std::string path = configObj["path"].get<std::string>();
            long long size = std::filesystem::file_size(path);
            result["data"] = size;
           
        }
        else if (message_name._Starts_with("isFolder"))
        {
            std::string path = configObj["path"].get<std::string>();
            auto flag = std::filesystem::is_directory(path);
            result["data"] = flag;
        }
        else if (message_name._Starts_with("getLastWriteTime"))
        {
            std::string path = configObj["path"].get<std::string>();
            auto lstTime = std::filesystem::last_write_time(path);
            auto span = std::filesystem::file_time_type::clock::now().time_since_epoch() - std::chrono::system_clock::now().time_since_epoch();
            auto elapse = std::chrono::duration_cast<std::chrono::milliseconds>(span).count();
            auto systemTime = std::chrono::duration_cast<std::chrono::milliseconds>(lstTime.time_since_epoch()).count() - elapse;
            result["data"] = systemTime;
        }
        else if (message_name._Starts_with("readFileFromPosition"))
        {
            std::string path = configObj["path"].get<std::string>();
            long long position = configObj["position"].get<long long>();
            long long bufferSize = configObj["bufferSize"].get<long long>();
            long long fileSize = std::filesystem::file_size(path);
            result["fileSize"] = fileSize;
            std::wifstream reader;
            reader.open(path, std::ios::binary);
            if (!reader.is_open()) {
                result["success"] = false;
            }
            else
            {
                reader.seekg(position, std::ios_base::beg);
                if (fileSize - position < bufferSize) {
                    bufferSize = fileSize - position;
                }
                wchar_t* buffer = new wchar_t[bufferSize + 1];
                buffer[bufferSize] = '\0';
                reader.read(buffer, bufferSize);
                std::string temp(utf8_conv.to_bytes(buffer));
                result["data"] = temp;
                delete[] buffer;
            }
        }
        else if(message_name._Starts_with("readFile"))
        {
            std::string path = configObj["path"].get<std::string>();
            long long bufferSize = configObj["bufferSize"].get<int>();
            CefPostTask(TID_UI, base::BindOnce(&readFile, path,bufferSize, frame,msg));
            return true;
        }
        else if (message_name._Starts_with("writeFile"))
        {
            std::string path = configObj["path"].get<std::string>();
            std::string existThen = configObj["existThen"].get<std::string>();
            std::string notExistThen = configObj["notExistThen"].get<std::string>();
            std::string data = configObj["data"].get<std::string>();
            bool isExist = std::filesystem::exists(path);
            if (isExist) {
                if (existThen == "error") {
                    result["success"] = false;
                    result["error"] = "文件已存在";
                }
                else if (existThen == "cover")
                {
                    std::ofstream writer;
                    writer.open(path, std::ios::out); //todo
                    writer.write(data.c_str(),data.length());
                    writer.close();
                }
                else if (existThen == "append") {
                    std::ofstream writer;
                    writer.open(path, std::ios::app); //todo
                    writer.write(data.c_str(), data.length());
                    writer.close();
                }
            }
            else
            {
                if (notExistThen == "error") {
                    result["success"] = false;
                    result["error"] = "文件不存在";
                }
                else if (notExistThen == "create")
                {
                    std::ofstream writer;
                    writer.open(path, std::ios::out); //todo
                    writer.write(data.c_str(), data.length());
                    writer.close();
                }
            }
        } else if (message_name._Starts_with("copy")) {
            std::string src = configObj["src"].get<std::string>();
            std::string dest = configObj["dest"].get<std::string>();
            wxString src1 = wxString::FromUTF8(src);
            wxString dest1 = wxString::FromUTF8(dest);
            wxCopyFile(src1, dest1);
        }
        auto resultStr = result.dump();
        CefRefPtr<CefListValue> msgArgs = msg->GetArgumentList();
        msgArgs->SetString(0, resultStr);
        frame->SendProcessMessage(PID_RENDERER, msg);
        return true;
    }
private:
    static void readFile(const std::string& path, long long bufferSize,CefRefPtr<CefFrame> frame, CefRefPtr<CefProcessMessage> msg)
    {
        json result;
        result["success"] = true;
        long long fileSize = std::filesystem::file_size(path);
        result["fileSize"] = fileSize;
        result["finished"] = false;
        std::wifstream reader;
        CefRefPtr<CefListValue> msgArgs = msg->GetArgumentList();
        reader.open(path, std::ios::binary);
        if (!reader.is_open()) {
            result["success"] = false;
            auto resultStr = result.dump();
            msgArgs->SetString(0, resultStr);
            frame->SendProcessMessage(PID_RENDERER, msg);
            return ;
        }
        static std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
        auto size = bufferSize;
        while (reader.tellg() < fileSize)
        {
            auto remainSize = fileSize - reader.tellg();
            if (bufferSize > remainSize) {
                size = remainSize;
            }
            wchar_t* buffer = new wchar_t[size + 1];
            buffer[size] = '\0';
            reader.read(buffer, size);
            std::string temp(utf8_conv.to_bytes(buffer));
            result["data"] = temp;
            delete[] buffer;
            if (reader.tellg() < fileSize) {

                auto resultStr = result.dump();
                msgArgs->SetString(0, resultStr);
                frame->SendProcessMessage(PID_RENDERER, msg);
            }
        }
        reader.close();
        result["finished"] = true;
        auto resultStr = result.dump();
        msgArgs->SetString(0, resultStr);
        frame->SendProcessMessage(PID_RENDERER, msg);
    }
    static bool sendMsg() {
    }
};