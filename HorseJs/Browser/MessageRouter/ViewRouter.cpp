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
void ViewRouter::removeView(int id) {
	int index = -1;
	for (int i = 0; i < views.size(); i++) {
		if (views.at(i)->GetID() == id) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		//todo error
		return;
	}
	views.erase(views.begin() + index);
}
void ViewRouter::setVisible(const nlohmann::json& message) {
	int index = -1;
	auto viewId = message["params"]["viewId"].get<int>();
	auto visible = message["params"]["visible"].get<bool>();
	for (int i = 0; i < views.size(); i++) {		
		if (viewId == views.at(i)->GetID()) {
			views.at(i)->SetVisible(visible);
			break;
		}
	}
	auto wsClient = WebSocketClient::getInstance();
	nlohmann::json backMsg = { {"__msgId", message["__msgId"].get<double>()} };
	std::string msgStr = backMsg.dump();
	wsClient->sendMessage(msgStr);
}