#pragma once
#include "json.hpp"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/file.h>

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
        auto userConfigPath = std::filesystem::current_path().append("app/horse.config.json").wstring();
        auto defaultConfigPath = std::filesystem::current_path().append("DefaultConfig.json").wstring();
        wxFile defaultConfigFile(defaultConfigPath);
        wxString defaultConfigText;
        defaultConfigFile.ReadAll(&defaultConfigText);
        config_ = json::parse(defaultConfigText.ToStdString());
        if (wxFile::Exists(userConfigPath)) {
            wxFile userConfigFile(userConfigPath);
            wxString userConfigText;
            userConfigFile.ReadAll(&userConfigText);
            json userConfig = json::parse(userConfigText.ToStdString());
            config_.merge_patch(userConfig);
        }
        return config_;
    };
    
};
