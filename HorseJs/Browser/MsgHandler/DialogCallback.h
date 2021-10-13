#pragma once
#include "include/wrapper/cef_message_router.h"
#include "include/cef_browser.h"
class DialogCallback : public CefRunFileDialogCallback
{
public:
	DialogCallback(CefRefPtr<CefProcessMessage> message, CefRefPtr<CefFrame> frame):message(message),frame(frame)
	{};
	void OnFileDialogDismissed(int selected_accept_filter, const std::vector<CefString>& file_paths) OVERRIDE
	{
		CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(message->GetName());
		CefRefPtr<CefListValue> msgArgs = msg->GetArgumentList();
		msgArgs->SetSize(1);
		std::string jsonStr = "{err:false,result:[";
		for (size_t i = 0; i < file_paths.size(); i++)
		{
			if (i != 0) jsonStr += ",";
			jsonStr += "'" + file_paths[i].ToString() + "'";
		}
		jsonStr += "]}";
		msgArgs->SetString(0, jsonStr);
		frame->SendProcessMessage(PID_RENDERER, msg);
	}
private:
	CefRefPtr<CefProcessMessage> message;
	CefRefPtr<CefFrame> frame;
	IMPLEMENT_REFCOUNTING(DialogCallback);
	DISALLOW_COPY_AND_ASSIGN(DialogCallback);
};
