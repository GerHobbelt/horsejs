#pragma once
#include "../../json/json.hpp"
#include "include/views/cef_browser_view.h"
#include "include/wrapper/cef_helpers.h"
class AppRouter : public virtual CefBaseRefCounted
{
public:
	AppRouter(const AppRouter&) = delete;
	AppRouter& operator=(const AppRouter&) = delete;
	static CefRefPtr<AppRouter> getInstance();
	void routeMessage(const nlohmann::json& message, bool isFromNodeProcess, nlohmann::json& result, CefRefPtr<CefFrame> frame);
private:
	IMPLEMENT_REFCOUNTING(AppRouter);
	AppRouter() = default;
};

