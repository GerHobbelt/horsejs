#pragma once
#include "../../json/json.hpp"
#include "include/views/cef_browser_view.h"
#include "include/wrapper/cef_helpers.h"
#include "../MessageProcessor/ViewDelegate.h"

class DialogRouter : public virtual CefBaseRefCounted
{
public:
	DialogRouter(const DialogRouter&) = delete;
	DialogRouter& operator=(const DialogRouter&) = delete;
	static CefRefPtr<DialogRouter> getInstance();
	void routeMessage(const nlohmann::json& message, bool isFromNodeProcess, nlohmann::json& result, CefRefPtr<CefFrame> frame);
private:
	IMPLEMENT_REFCOUNTING(DialogRouter);
	DialogRouter() = default;
};

