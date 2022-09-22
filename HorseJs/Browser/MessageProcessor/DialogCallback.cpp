#include "DialogCallback.h"
void DialogCallback::OnFileDialogDismissed(const std::vector<CefString>& file_paths)
{
	auto pathCount = file_paths.size();
	if (pathCount == 1) {
		result["data"] = file_paths[0].ToString();
	}
	else {
		result["data"] = {};
		for (size_t i = 0; i < file_paths.size(); i++) {
			result["data"].push_back(file_paths[i].ToString());
		}
	}
	if (isFromNodeProcess) {
		WebSocketClient::getInstance()->sendMessage(result);
	}
	else
	{
		std::string resultStr = result.dump();
		CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(resultStr);
		frame->SendProcessMessage(PID_RENDERER, msg);
	}
}