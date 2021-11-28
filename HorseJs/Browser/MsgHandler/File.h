#pragma once
#include <fstream>
#include <filesystem>
#include <codecvt> // codecvt_utf8
#include <locale>  // wstring_convert
#include <sstream>
#include "include/wrapper/cef_message_router.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_closure_task.h"

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
        CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(message->GetName());        
        //msgArgs->SetSize(1);
        if (message_name._Starts_with("readDir"))
        {
            static std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
            std::string folderPath = configObj["path"].get<std::string>();
            result["data"] = json::array();
            for (auto& itr : std::filesystem::directory_iterator(folderPath))
            {
                auto pathStr = itr.path().wstring();
                result["data"].push_back(utf8_conv.to_bytes(pathStr));
            }
        }
        else if (message_name._Starts_with("getFileSize"))
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
            std::string from = configObj["from"].get<std::string>();
            std::ios_base::seekdir seekFrom = 0;
            if (from == "start") {
                seekFrom = std::ios_base::beg;
            }
            else if(from == "end")
            {
                seekFrom = std::ios_base::end;
            }
            else
            {
                seekFrom = std::ios_base::cur;
            }
            std::ifstream reader;
            reader.open(path, std::ios::in);
            if (!reader.is_open()) {
                result["success"] = false;
                auto resultStr = result.dump();
                //msgArgs->SetString(0, resultStr);
                frame->SendProcessMessage(PID_RENDERER, msg);
                return true;
            }
            reader.seekg(position, seekFrom);
            char* buf = new char[bufferSize]; //64k
            //while (true)
            //{
            //    reader.read(buf, bufferSize);
            //    if(reader.eof)
            //}
            //reader.re
            //result["data"] = systemTime;
        }
        else if(message_name._Starts_with("readFile"))
        {
            std::string path = configObj["path"].get<std::string>();
            long long bufferSize = configObj["bufferSize"].get<int>();
            CefPostTask(TID_UI, base::Bind(&readFile, path,bufferSize, frame,msg));
            return true;
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