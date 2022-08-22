#include "Config.h"
#include <filesystem>
#include <fstream>
#include <iterator>

json Config::get() {
    namespace fs = std::filesystem;
    static json  config_;
    if (!config_.is_null()) return config_;
    auto configFile = fs::current_path().append("config.json");
    if (fs::exists(configFile)) {
        std::ifstream in(configFile);
        std::istreambuf_iterator<char> begin(in),end;
        std::string configStr(begin, end);
        config_ = json::parse(configStr);
    }
    else {
        //todo message box show win/mac
    }
    return config_;
};