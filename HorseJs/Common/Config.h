#pragma once
#include "json.hpp"
#include <fstream>
#include <filesystem>
#include <iostream>
using nlohmann::json;
class Config
{
private:
	Config()=delete;
	~Config()=delete;
public:
    static json get() {
        static json  config_;
        if (!config_.is_null()) return config_;
        auto targetPath = std::filesystem::current_path();
        //todo 如果没有这个文件
        targetPath.append("app/horse.config.json");
        std::ifstream reader;
        reader.open(targetPath, std::ios::in);
        std::stringstream buffer;
        buffer << reader.rdbuf();
        reader.close();
        auto configCode = buffer.str();
        config_ = json::parse(configCode);
        return config_;
    };
    
};
