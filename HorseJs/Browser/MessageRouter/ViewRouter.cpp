#include "ViewRouter.h"
#include "../MessageProcessor/ViewDelegate.h"
#include "../WebSocketClient.h"
#include "../MessageProcessor/PageHandler.h"

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

void ViewRouter::routeMessage(const nlohmann::json& message, CefRefPtr<CefBrowserView> view, nlohmann::json& result) {
	auto actionName = message["__actionName"].get<std::string>();
	if (view == nullptr) {
		auto viewId = message["viewId"].get<int>();
		view = this->getViewById(viewId);
	}
	if (actionName == "setVisible") {
		auto visible = message["visible"].get<bool>();
		view->SetVisible(visible);
	}
	else if (actionName == "getUrl") {
		result["url"] = view->GetBrowser()->GetMainFrame()->GetURL();
	}
	else if (actionName == "showOpenFileDialog") {
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
	else if (actionName == "devTools") {
		CefBrowserSettings browserSettings;
		CefWindowInfo windowInfo;
		auto handler = PageHandler::getInstance();
		auto option = message["option"].get<std::string>();
		if (option == "open") {
			view->GetBrowser()->GetHost()->ShowDevTools(windowInfo, handler, browserSettings, CefPoint());
		}
		else {
			view->GetBrowser()->GetHost()->CloseDevTools();
		}
	}
	result["__msgId"] = message["__msgId"].get<int64>();
	WebSocketClient::getInstance()->sendMessage(result);
}