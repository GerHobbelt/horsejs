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
	CefRefPtr<WindowDelegate> getWindowDelegateById(int winId);
	void routeMessage(const nlohmann::json& message,bool isFromNodeProcess, nlohmann::json& result);
private:
	IMPLEMENT_REFCOUNTING(WindowRouter);
	WindowRouter() = default;
	std::vector<CefRefPtr<WindowDelegate>> windows;
};

