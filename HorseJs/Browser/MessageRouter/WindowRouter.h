#pragma once
#include "../../json/json.hpp"
#include "include/cef_app.h"
#include "include/wrapper/cef_helpers.h"
#include "../MessageProcessor/WindowDelegate.h"
class WindowRouter : public virtual CefBaseRefCounted
{
public:
	WindowRouter(const WindowRouter&) = delete;
	WindowRouter& operator=(const WindowRouter&) = delete;
	static CefRefPtr<WindowRouter> getInstance();
	void removeWindow(WindowDelegate* tar);
	void routeMessage(const nlohmann::json& message, CefRefPtr<WindowDelegate> winDelegate, nlohmann::json& result);
private:
	IMPLEMENT_REFCOUNTING(WindowRouter);
	WindowRouter() = default;
	CefRefPtr<WindowDelegate> getWindowDelegateById(const nlohmann::json& message);
	void returnMessage(nlohmann::json& backMsg, const nlohmann::json& message);
	std::vector<CefRefPtr<WindowDelegate>> windows;
};

