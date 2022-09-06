#pragma once
#include "../../json/json.hpp"
#include "include/views/cef_browser_view.h"
#include "include/wrapper/cef_helpers.h"
class ViewRouter : public virtual CefBaseRefCounted
{
public:
	ViewRouter(const ViewRouter&) = delete;
	ViewRouter& operator=(const ViewRouter&) = delete;

	static CefRefPtr<ViewRouter> getInstance();
	CefRefPtr<CefBrowserView> createView(std::string& url);
	void removeView(int id);
	void setVisible(const nlohmann::json& message);
	void openDevTools(const nlohmann::json& message);
private:
	IMPLEMENT_REFCOUNTING(ViewRouter);
	ViewRouter() = default;
	int getViewIndexById(int id);
	std::vector<CefRefPtr<CefBrowserView>> views;
};

