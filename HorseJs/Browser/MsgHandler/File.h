#pragma once
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/cef_task.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"
#include "include/base/cef_callback.h"
#include "wx/filefn.h"
#include <wx/ffile.h>
#include "Helper.h"


#include "../../Common/json.hpp"
using nlohmann::json;
class File
{
public:
    File() = delete;
    // convert string to wstring
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        std::string msgName = message->GetName();
        std::string filter = Helper::getFilter(message);
        json configObj = Helper::getConfig(message);
        json result;
        result["success"] = true;
        if (filter == "getFileSize")
        {
            auto path = Helper::convertString(configObj["path"].get<std::string>());
            long long size = std::filesystem::file_size(path);
            result["data"] = size;           
        }
        else if (filter == "getLastWriteTime")
        {
            auto path = Helper::convertString(configObj["path"].get<std::string>());
            auto lstTime = std::filesystem::last_write_time(path);
            auto span = std::filesystem::file_time_type::clock::now().time_since_epoch() - std::chrono::system_clock::now().time_since_epoch();
            auto elapse = std::chrono::duration_cast<std::chrono::milliseconds>(span).count();
            auto systemTime = std::chrono::duration_cast<std::chrono::milliseconds>(lstTime.time_since_epoch()).count() - elapse;
            result["data"] = systemTime;
        }
        else if (filter == "readFileFromPosition")
        {
            auto path = Helper::convertString(configObj["path"].get<std::string>());
            long long position = configObj["position"].get<long long>();
            long long bufferSize = configObj["bufferSize"].get<long long>();
            wxFile file;
            bool flag = file.Open(path);
            if (!flag) {
                result["success"] = false;
                result["error"] = "无法打开文件";
            }
            else
            {
                wxFileOffset fileSize = file.Length();
                if (fileSize <= position) {
                    file.Close();
                    result["success"] = false;
                    result["fileSize"] = fileSize;
                    result["error"] = "读取位置超出文件大小";
                }
                else
                {
                    auto remainLength = fileSize - position;
                    if (remainLength < bufferSize) {
                        bufferSize = remainLength;
                    }
                    file.Seek(position);
                    unsigned char* buffer = new unsigned char[bufferSize];
                    file.Read(buffer, bufferSize);
                    CefRefPtr<CefBinaryValue> data = CefBinaryValue::Create(buffer, bufferSize);
                    Helper::SendMsg(frame, msgName + "_data", data);
                    delete[] buffer;
                    file.Close();
                }
            }            
        }
        else if(filter == "readFile")
        {
            auto path = Helper::convertString(configObj["path"].get<std::string>());
            long long bufferSize = configObj["bufferSize"].get<int>();
            CefPostTask(TID_UI, base::BindOnce(&readFile, path,bufferSize, frame, msgName));
        }
        else if (filter == "writeFile")
        {
            auto path = Helper::convertString(configObj["path"].get<std::string>());
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
        } else if (filter == "copy") {
            std::string src = configObj["src"].get<std::string>();
            std::string dest = configObj["dest"].get<std::string>();
            wxString src1 = wxString::FromUTF8(src);
            wxString dest1 = wxString::FromUTF8(dest);
            wxCopyFile(src1, dest1);
        }
        Helper::SendMsg(frame, msgName, result);
        return true;
    }
private:
    //static void readFileFromPosition(const std::wstring& path, long long bufferSize, long long position, CefRefPtr<CefFrame> frame, const std::string& msgName)
    //{
    //    wxFile file;
    //    bool flag = file.Open(path);
    //    if (!flag) {
    //        json result;
    //        result["success"] = false;
    //        result["error"] = "无法打开文件";
    //        Helper::SendMsg(frame, msgName + "_data_finish", result);
    //        return;
    //    }
    //    wxFileOffset fileSize = file.Length();
    //    if (fileSize <= position) {
    //        file.Close();
    //        json result;
    //        result["success"] = false;
    //        result["fileSize"] = fileSize;
    //        result["error"] = "读取位置超出文件大小";
    //        Helper::SendMsg(frame, msgName + "_data_finish", result);
    //        return;
    //    }
    //    auto remainLength = fileSize - position;
    //    if (remainLength < bufferSize) {
    //        bufferSize = remainLength;
    //    }
    //    file.Seek(position);
    //    unsigned char* buffer = new unsigned char[bufferSize];
    //    file.read(buffer, bufferSize);
    //    CefRefPtr<CefBinaryValue> data = CefBinaryValue::Create(buffer, bufferSize);
    //    Helper::SendMsg(frame, msgName + "_data", data);
    //    delete[] buffer;
    //    file.Close();
    //    json result;
    //    result["success"] = true;
    //    result["fileSize"] = fileSize;
    //    Helper::SendMsg(frame, msgName + "_data_finish", result);
    //}
    static void readFile(const std::wstring& path, long long bufferSize,CefRefPtr<CefFrame> frame, const std::string& msgName)
    {
        wxFile file;
        bool flag = file.Open(path);
        if (!flag) {
            json result;
            result["success"] = false;
            result["error"] = "无法打开文件";
            Helper::SendMsg(frame, msgName + "_data_finish", result);
            return;
        }
        wxFileOffset fileSize = file.Length();
        auto size = bufferSize;
        while (!file.Eof())
        {
            wxFileOffset position = file.Tell();
            wxFileOffset leftSize = fileSize - position;
            if (leftSize < size) {
                size = leftSize;
            }
            unsigned char* buffer = new unsigned char[size];
            file.Read(buffer, size);
            CefRefPtr<CefBinaryValue> data = CefBinaryValue::Create(buffer, size);
            Helper::SendMsg(frame, msgName + "_data", data);
            delete[] buffer;
        }
        file.Close();
        json result;
        result["success"] = true;
        result["fileSize"] = fileSize;
        Helper::SendMsg(frame, msgName + "_data_finish", result);
    }
};