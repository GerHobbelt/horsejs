#include "Config.h"
#include <filesystem>
#include <fstream>
nlohmann::json config;
namespace fs = std::filesystem;
namespace Config {
    void init() {
        //todo 这个路径有问题
        auto configFile = fs::current_path().append("config.json");
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
