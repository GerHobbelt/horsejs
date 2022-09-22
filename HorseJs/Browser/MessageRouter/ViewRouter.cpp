#include "ViewRouter.h"
#include "../MessageProcessor/ViewDelegate.h"
#include "../WebSocketClient.h"
#include "../MessageProcessor/PageHandler.h"
#include "../MessageProcessor/DialogCallback.h"
namespace {
	CefRefPtr<ViewRouter> instance = nullptr;
}

CefRefPtr<ViewRouter> ViewRouter::getInstance() {
	if (!instance) {
		instance = new ViewRouter();
	}
	return instance;
}

CefRefPtr<CefBrowserView> ViewRouter::createView(std::string& url,int winId,int mainViewId) {
	CefBrowserSettings settings;
	auto pageHandler = PageHandler::getInstance();
	//todo 这个应该是有用的，但目前还没用上
	//CefRefPtr<ViewDelegate> viewDelegate = new ViewDelegate();
	CefRefPtr<CefDictionaryValue> extraInfo = CefDictionaryValue::Create();
	auto viewId = views.size();
	extraInfo->SetInt("curViewId", viewId);
	extraInfo->SetInt("mainViewId", mainViewId);
	extraInfo->SetInt("winId", winId);
	auto view = CefBrowserView::CreateBrowserView(pageHandler, url, settings, extraInfo, nullptr, nullptr);
	view->SetID(viewId);
	views.push_back(view);
	return view;
}
CefRefPtr<CefBrowserView> ViewRouter::getViewById(int viewId) {
	int index = -1;
	for (int i = 0; i < views.size(); i++) {
		if (views.at(i)->GetID() == viewId) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		//todo error
	}
	return views.at(index);
}

void ViewRouter::_removeView(int id) {
	int index = -1;
	for (int i = 0; i < views.size(); i++) {
		if (views.at(i)->GetID() == id) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		//todo error
	}
	views.erase(views.begin() + index);
}

void ViewRouter::routeMessage(const nlohmann::json& message, bool isFromNodeProcess, nlohmann::json& result, CefRefPtr<CefFrame> frame) {
	auto actionName = message["__actionName"].get<std::string>();
	auto viewId = message["__viewId"].get<int>();
	auto view = this->getViewById(viewId);
	if (actionName == "setVisible") {
		auto visible = message["visible"].get<bool>();
		view->SetVisible(visible);
	}
	else if (actionName == "getUrl") {
		std::string url = view->GetBrowser()->GetMainFrame()->GetURL();
		result["url"] = url;
	}
	else if (actionName == "devTools") {
		CefBrowserSettings browserSettings;
		CefWindowInfo windowInfo;
		CefRefPtr<PageHandler> handler = PageHandler::getInstance();
		auto option = message["option"].get<std::string>();
		if (option == "open") {
			view->GetBrowser()->GetHost()->ShowDevTools(windowInfo, handler, browserSettings, CefPoint());
		}
		else {
			view->GetBrowser()->GetHost()->CloseDevTools();
		}
	}
	else if (actionName == "showFileOrFolderDialog") {
		CefBrowserHost::FileDialogMode mode;
		auto title = message["title"].get<std::string>();
		auto defaultPath = message["defaultPath"].get<std::string>();
		auto type = message["type"].get<std::string>();
		std::vector<CefString> fileFilters;
		for (const std::string& var : message["filters"])
		{
			fileFilters.push_back(var);
		}
		CefRefPtr<CefRunFileDialogCallback> dcb = new DialogCallback(result, frame, isFromNodeProcess);
		if (type == "openFile")
		{
			mode = message["multiSelection"].get<bool>() ? FILE_DIALOG_OPEN_MULTIPLE : FILE_DIALOG_OPEN;
			view->GetBrowser()->GetHost()->RunFileDialog(mode, title, defaultPath, fileFilters, dcb);
		}
		else if (type == "openFolder")
		{
			mode = FILE_DIALOG_OPEN_FOLDER;
			view->GetBrowser()->GetHost()->RunFileDialog(mode, title, defaultPath, fileFilters, dcb);
		}		
		return;
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
	else
	{
		std::string resultStr = result.dump();
		CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(resultStr);
		frame->SendProcessMessage(PID_RENDERER, msg);
	}
}