#pragma once
#include "../../json/json.hpp"
#include "include/views/cef_browser_view.h"
#include "include/wrapper/cef_helpers.h"
#include "../WebSocketClient.h"
class DialogRouter : public virtual CefBaseRefCounted
{
	void routeMessage(const nlohmann::json& message, bool isFromNodeProcess, nlohmann::json& result);
};

