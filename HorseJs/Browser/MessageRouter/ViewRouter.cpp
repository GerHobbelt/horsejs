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

CefRefPtr<CefBrowserView> ViewRouter::createView(std::string& url) {
	CefBrowserSettings settings;
	auto pageHandler = PageHandler::getInstance();
	CefRefPtr<ViewDelegate> viewDelegate = new ViewDelegate();
	auto view = CefBrowserView::CreateBrowserView(pageHandler, url, settings, nullptr, nullptr, nullptr);
	view->SetID(views.size());
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
	else if (actionName == "devTools") {
		CefBrowserSettings browserSettings;
		CefWindowInfo windowInfo;
		CefPoint mousePoint(100, 100); //todo 得到当前鼠标所在位置
		auto handler = PageHandler::getInstance();
		auto option = message["option"].get<std::string>();
		if (option == "open") {
			view->GetBrowser()->GetHost()->ShowDevTools(windowInfo, handler, browserSettings, mousePoint);
		}
		else {
			view->GetBrowser()->GetHost()->CloseDevTools();
		}
	}
	result["__msgId"] = message["__msgId"].get<int64>();
	WebSocketClient::getInstance()->sendMessage(result);
}