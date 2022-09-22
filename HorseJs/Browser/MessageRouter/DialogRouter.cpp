#include "DialogRouter.h"
void DialogRouter::routeMessage(const nlohmann::json& message, bool isFromNodeProcess, nlohmann::json& result) {
	auto actionName = message["__actionName"].get<std::string>();
	if (actionName == "showOpenFileDialog") {
		CefBrowserHost::FileDialogMode mode = FILE_DIALOG_OPEN_MULTIPLE;// FILE_DIALOG_OPEN;
		//view->GetBrowser()->GetHost()->RunFileDialog();
	}
	else if (actionName == "showOpenFolderDialog") {
		//view->GetBrowser()->GetHost()->RunFileDialog();
	}
	else if (actionName == "showSaveFileDialog") {
		//view->GetBrowser()->GetHost()->RunFileDialog();
	}
	else if (actionName == "showMessageDialog") {
		//view->GetBrowser()->GetHost()->RunFileDialog();
	}
	else if (actionName == "showErrorDialog") {
		//view->GetBrowser()->GetHost()->RunFileDialog();
	}
	if (isFromNodeProcess) {
		WebSocketClient::getInstance()->sendMessage(result);
	}
}