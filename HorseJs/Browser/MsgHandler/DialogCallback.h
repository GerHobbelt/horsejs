#pragma once
#include "include/wrapper/cef_message_router.h"
#include "include/cef_browser.h"
#include "../../Common/json.hpp"
using nlohmann::json;
class DialogCallback : public CefRunFileDialogCallback
{
public:
	DialogCallback(CefRefPtr<CefProcessMessage> message, CefRefPtr<CefFrame> frame):message(message),frame(frame)
	{};
	void OnFileDialogDismissed(int selected_accept_filter, const std::vector<CefString>& file_paths) override
	{
		//todo 不必要整个message，只要message->GetName()即可
		CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(message->GetName());
		CefRefPtr<CefListValue> msgArgs = msg->GetArgumentList();
		msgArgs->SetSize(1);
		json result;
		result["success"] = true;
		result["data"] = {};
		for (size_t i = 0; i < file_paths.size(); i++)
		{
			result["data"].push_back(file_paths[i].ToString());
		}
		msgArgs->SetString(0, result.dump());
		frame->SendProcessMessage(PID_RENDERER, msg);
	}
private:
	CefRefPtr<CefProcessMessage> message;
	CefRefPtr<CefFrame> frame;
	IMPLEMENT_REFCOUNTING(DialogCallback);
	DISALLOW_COPY_AND_ASSIGN(DialogCallback);
};
