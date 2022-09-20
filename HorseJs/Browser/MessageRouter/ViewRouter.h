#pragma once
#include "../../json/json.hpp"
#include "include/views/cef_browser_view.h"
#include "include/wrapper/cef_helpers.h"
#include "../MessageProcessor/ViewDelegate.h"
class ViewRouter : public virtual CefBaseRefCounted
{
public:
	ViewRouter(const ViewRouter&) = delete;
	ViewRouter& operator=(const ViewRouter&) = delete;
	CefRefPtr<CefBrowserView> getViewById(int viewId);
	static CefRefPtr<ViewRouter> getInstance();
	CefRefPtr<CefBrowserView> createView(std::string& url);
	void _removeView(int id);
	void routeMessage(const nlohmann::json& message, CefRefPtr<CefBrowserView> view, nlohmann::json& result);
private:
	IMPLEMENT_REFCOUNTING(ViewRouter);
	ViewRouter() = default;
	std::vector<CefRefPtr<CefBrowserView>> views;
};

