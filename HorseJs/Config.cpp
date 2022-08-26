#include "Config.h"
#include <filesystem>
#include <fstream>
#include <Windows.h>
nlohmann::json config;
namespace fs = std::filesystem;
namespace Config {
    fs::path getExeDir() {
        //todo mac
        WCHAR _exePath[MAX_PATH];
        DWORD result = GetModuleFileName(NULL, _exePath, MAX_PATH);
        if (result == 0) {
            throw "Error in getting module filename.";
        }
        std::wstring exePathStr(_exePath);
        auto exePath = fs::path(exePathStr);
        return exePath.remove_filename();
    }
    void init() {
        //todo 这个路径有问题
        auto configFile = getExeDir().append("config.json");
        if (fs::exists(configFile)) {
            std::ifstream in(configFile);
            std::istreambuf_iterator<char> begin(in), end;
            std::string configStr(begin, end);
            config = nlohmann::json::parse(configStr);
        }
        else {
            //todo message box show win/mac
        }
    }
}
