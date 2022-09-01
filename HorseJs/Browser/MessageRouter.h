#pragma once

#include "../json/json.hpp"
namespace MessageRouter
{
	void route(const nlohmann::json& message);
};

