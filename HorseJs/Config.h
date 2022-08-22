#pragma once
#include "json/json.hpp"
using nlohmann::json;
class Config
{
public:
	static json get();
private:
	Config() = delete;
	~Config() = delete;
};

