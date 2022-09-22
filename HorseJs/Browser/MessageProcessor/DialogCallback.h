#pragma once
#include "../../json/json.hpp"
#include "include/views/cef_browser_view.h"
#include "include/wrapper/cef_helpers.h"
#include "../WebSocketClient.h"
#include "../../json/json.hpp"
class DialogCallback: public CefRunFileDialogCallback
{
public:
	DialogCallback(const nlohmann::json& result, CefRefPtr<CefFrame> frame,bool isFromNodeProcess) :result(result), frame(frame), isFromNodeProcess(isFromNodeProcess) {};
	virtual void OnFileDialogDismissed(const std::vector<CefString>& file_paths) override;
private:
	nlohmann::json result;
	CefRefPtr<CefFrame> frame;
	bool isFromNodeProcess;
	IMPLEMENT_REFCOUNTING(DialogCallback);
	DISALLOW_COPY_AND_ASSIGN(DialogCallback);
};

