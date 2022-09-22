#include "DialogRouter.h"
#include "../WebSocketClient.h"
#include "../MessageProcessor/DialogCallback.h"
#include "ViewRouter.h"
namespace {
	CefRefPtr<DialogRouter> instance = nullptr;
}

CefRefPtr<DialogRouter> DialogRouter::getInstance() {
	if (!instance) {
		instance = new DialogRouter();
	}
	return instance;
}

void DialogRouter::routeMessage(const nlohmann::json& message, bool isFromNodeProcess, nlohmann::json& result, CefRefPtr<CefFrame> frame) {
	auto actionName = message["__actionName"].get<std::string>();
	auto viewId = message["__viewId"].get<int>();
	auto view = ViewRouter::getInstance()->getViewById(viewId);
	if (actionName == "showOpenFileDialog") {
		CefBrowserHost::FileDialogMode mode = message["multiSelections"].get<bool>() ? FILE_DIALOG_OPEN_MULTIPLE : FILE_DIALOG_OPEN;
		auto title = message["title"].get<std::string>();
		auto defaultPath = message["defaultPath"].get<std::string>();
		std::vector<CefString> fileFilters;
		for (const std::string& var : message["filters"])
		{
			fileFilters.push_back(var);
		}
		CefRefPtr<CefRunFileDialogCallback> dcb = new DialogCallback(result, frame,isFromNodeProcess);
		view->GetBrowser()->GetHost()->RunFileDialog(mode, title, defaultPath, fileFilters, dcb);
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
}