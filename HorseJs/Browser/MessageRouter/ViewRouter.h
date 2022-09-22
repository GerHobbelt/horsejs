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
	CefRefPtr<CefBrowserView> createView(std::string& url, int winId,int mainViewId);
	void _removeView(int id);
	void routeMessage(const nlohmann::json& message, bool isFromNodeProcess, nlohmann::json& result, CefRefPtr<CefFrame> frame);
private:
	IMPLEMENT_REFCOUNTING(ViewRouter);
	ViewRouter() = default;
	std::vector<CefRefPtr<CefBrowserView>> views;
};

