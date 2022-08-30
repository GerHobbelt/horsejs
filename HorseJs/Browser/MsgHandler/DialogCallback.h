#pragma once
#include "include/wrapper/cef_message_router.h"
#include "include/cef_browser.h"
#include "../../Common/json.hpp"
#include "Helper.h"

using nlohmann::json;
class DialogCallback : public CefRunFileDialogCallback
{
public:
	DialogCallback(std::string& msgName, CefRefPtr<CefFrame> frame):msgName(msgName),frame(frame)
	{};
	void OnFileDialogDismissed(int selected_accept_filter, const std::vector<CefString>& file_paths) override
	{
		json result;
		result["success"] = true;
		result["data"] = {};
		for (size_t i = 0; i < file_paths.size(); i++)
		{
			result["data"].push_back(file_paths[i].ToString());
		}
		Helper::SendMsg(frame, msgName, result);
	}
private:
	std::string msgName;
	CefRefPtr<CefFrame> frame;
	IMPLEMENT_REFCOUNTING(DialogCallback);
	DISALLOW_COPY_AND_ASSIGN(DialogCallback);
};
