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
	void createWindow(const nlohmann::json& message);
	void removeWindow(WindowDelegate* tar);
	void addView(const nlohmann::json& message);
	void removeView(const nlohmann::json& message);
	void hide(const nlohmann::json& message);
	void show(const nlohmann::json& message);
private:
	IMPLEMENT_REFCOUNTING(WindowRouter);
	WindowRouter() = default;
	int getWindowIndexById(int id);
	std::vector<CefRefPtr<WindowDelegate>> windows;
};

