#pragma once

#include "../json/json.hpp"
namespace MessageRouter
{
	void route(const nlohmann::json& message);
	void createWindow(const nlohmann::json& params);
	void createWindowMultiView(const nlohmann::json& params);
	void createWindowOverlayView(const nlohmann::json& params);
};

