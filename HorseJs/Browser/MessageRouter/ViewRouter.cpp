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
void ViewRouter::returnMessage(nlohmann::json& backMsg, const nlohmann::json& message) {
	auto wsClient = WebSocketClient::getInstance();
	backMsg["__msgId"] = message["__msgId"].get<double>();
	//todo 好像释放不了？这个要验证一下
	std::string msgStr = backMsg.dump();
	wsClient->sendMessage(msgStr);
}
CefRefPtr<CefBrowserView> ViewRouter::getViewById(const nlohmann::json& message) {
	auto id = message["params"]["viewId"].get<int>();
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
void ViewRouter::setVisible(const nlohmann::json& message) {	
	auto visible = message["params"]["visible"].get<bool>();
	auto view = getViewById(message);
	view->SetVisible(visible);
	auto wsClient = WebSocketClient::getInstance();
	nlohmann::json backMsg = {};
	returnMessage(backMsg, message);
}
void ViewRouter::openDevTools(const nlohmann::json& message) {
	auto view = getViewById(message);
	CefBrowserSettings browserSettings;
	CefWindowInfo windowInfo;
	CefPoint mousePoint(100, 100); //todo 得到当前鼠标所在位置
	auto handler = PageHandler::getInstance();
	auto option = message["params"]["option"].get<std::string>();
	if (option == "open") {
		view->GetBrowser()->GetHost()->ShowDevTools(windowInfo, handler, browserSettings, mousePoint);
	}
	else {
		view->GetBrowser()->GetHost()->CloseDevTools();
	}
	nlohmann::json backMsg = {};
	returnMessage(backMsg, message);
}
void ViewRouter::routeMessage(const nlohmann::json& message) {
	auto actionName = message["actionName"].get<std::string>();
	if (actionName == "setVisible") {
		setVisible(message);
	}
	else if (actionName == "devTools") {
		openDevTools(message);
	}
}