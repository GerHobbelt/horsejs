#pragma once
#include <wx/wx.h>
#include <wx/dynlib.h>

#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "../../Common/json.hpp"
#include "Helper.h"
using nlohmann::json;

typedef std::string(*execute)(std::string&, std::function<void(std::string&)> callback);

class Plugin
{
public:
    Plugin() = delete;
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        std::string msgName = message->GetName();
        std::string filter = Helper::getFilter(message);
        json result;
        result["success"] = true;
        json configObj = Helper::getConfig(message);
        std::string name = configObj["name"].get<std::string>();
        bool async = configObj["async"].get<bool>();
        configObj["paramObject"]["__async"] = async;
        if (filter == "load") {
            //todo try catch
            wxTheApp;
            wxDynamicLibrary* dl = new wxDynamicLibrary();
            wxString trueName = dl->CanonicalizeName(wxString::FromUTF8("plugins/" + name+"/"+name));
            dl->Load(trueName);
            //todo init
            libMap[name] = dl;
            execute exec = (execute)dl->GetSymbol("execute");
            funcMap[name][0] = exec;
            execute unload = (execute)dl->GetSymbol("unload");
            funcMap[name][1] = unload;
            execute init = (execute)dl->GetSymbol("init");
            json paramObj = configObj["paramObject"];
            paramObj["__appConfig"] = Config::get();
            auto str = paramObj.dump();
            auto resultStr = init(str,nullptr); //todo hasCallback
            json data = json::parse(resultStr);
            result["data"] = data;
        }
        else if (filter == "excute") {
            //todo try catch
            execute exec = funcMap[name][0];
            auto str = configObj["paramObject"].dump();
            std::string resultStr;
            if (async) {
                resultStr = exec(str, [&](std::string& callbackMsgStr) {
                   });
            }
            else
            {
                resultStr = exec(str, nullptr);
            }
            result["data"] = json::parse(resultStr);
        }
        else if (filter == "unload") {
            //todo try catch
            execute unload = funcMap[name][1];
            auto str = configObj["paramObject"].dump();
            auto resultStr = unload(str, nullptr);
            auto dl = libMap[name];
            delete dl;
            //todo unload
            libMap.erase(name);
            funcMap.erase(name);
            json data = json::parse(resultStr);
            result["data"] = data;
        }
        Helper::SendMsg(frame, msgName, result);
        return true;
    };
    static std::map<std::string, wxDynamicLibrary*> libMap;
    static std::map<std::string, execute[2]> funcMap;
};
std::map<std::string, execute[2]> Plugin::funcMap;
std::map<std::string, wxDynamicLibrary*> Plugin::libMap;
