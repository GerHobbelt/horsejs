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

int ViewRouter::getViewIndexById(int id) {
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
	return index;
}

void ViewRouter::_removeView(int id) {
	int index = getViewIndexById(id);
	views.erase(views.begin() + index);
}
void ViewRouter::setVisible(const nlohmann::json& message) {
	auto viewId = message["params"]["viewId"].get<int>();
	auto visible = message["params"]["visible"].get<bool>();
	int index = getViewIndexById(viewId);
	views.at(index)->SetVisible(visible);
	auto wsClient = WebSocketClient::getInstance();
	nlohmann::json backMsg = { {"__msgId", message["__msgId"].get<double>()} };
	std::string msgStr = backMsg.dump();
	wsClient->sendMessage(msgStr);
}
void ViewRouter::openDevTools(const nlohmann::json& message) {
	auto viewId = message["params"]["viewId"].get<int>();
	auto option = message["params"]["option"].get<std::string>();
	int index = getViewIndexById(viewId);
	CefBrowserSettings browserSettings;
	CefWindowInfo windowInfo;
	CefPoint mousePoint(100, 100); //todo 得到当前鼠标所在位置
	auto handler = PageHandler::getInstance();
	if (option == "open") {
		views.at(index)->GetBrowser()->GetHost()->ShowDevTools(windowInfo, handler, browserSettings, mousePoint);
	}
	else {
		views.at(index)->GetBrowser()->GetHost()->CloseDevTools();
	}
	auto wsClient = WebSocketClient::getInstance();
	nlohmann::json backMsg = { {"__msgId", message["__msgId"].get<double>()} };
	std::string msgStr = backMsg.dump();
	wsClient->sendMessage(msgStr);
}