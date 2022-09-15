#include "WindowRouter.h"
#include "../WebSocketClient.h"

namespace {
	CefRefPtr<WindowRouter> instance = nullptr;
}

CefRefPtr<WindowRouter> WindowRouter::getInstance() {
	if (!instance) {
		instance = new WindowRouter();
	}
	return instance;
}
void WindowRouter::returnMessage(nlohmann::json& backMsg,const nlohmann::json& message) {
	auto wsClient = WebSocketClient::getInstance();
	backMsg["__msgId"] = message["__msgId"].get<double>();
	//todo 好像释放不了？这个要验证一下
	std::string msgStr = backMsg.dump();
	wsClient->sendMessage(msgStr);
}
CefRefPtr<WindowDelegate> WindowRouter::getWindowDelegateById(const nlohmann::json& message) {
	auto id = message["__winId"].get<int>();
	int index = -1;
	for (int i = 0; i < windows.size(); i++) {
		if (windows.at(i)->win->GetID() == id) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		//todo error
	}
	auto winDelegate = windows.at(index);
	return winDelegate;
}

void WindowRouter::routeMessage(const nlohmann::json& message, CefRefPtr<WindowDelegate> winDelegate) {
	auto actionName = message["actionName"].get<std::string>();
	nlohmann::json backMsg = { };
	if (actionName == "createWindow") {
		auto winId = windows.size();
		CefRefPtr<WindowDelegate> winDelegate = new WindowDelegate(message["params"], winId);
		windows.push_back(winDelegate);
		backMsg["id"] = winId;
		returnMessage(backMsg, message);
	}
	else if (actionName == "addView") {
		if (winDelegate == nullptr) winDelegate = getWindowDelegateById(message);
		auto viewId = winDelegate->AddOverlayView(message["params"]);
		backMsg["id"] = viewId;
		returnMessage(backMsg, message);
	}
	else if (actionName == "hideAllView") {

	}
	else if (actionName == "removeView") {
		if (winDelegate == nullptr) winDelegate = getWindowDelegateById(message);
		auto viewId = message["params"]["viewId"].get<int>();
		winDelegate->removeView(viewId);
	}
	else if (actionName == "setVisible") {
		if (winDelegate == nullptr) winDelegate = getWindowDelegateById(message);
		auto visible = message["params"]["visible"].get<bool>();
		if (visible) {
			winDelegate->win->Show();
		}
		else {
			winDelegate->win->Hide();
		}
	}
	else if (actionName == "setTitle") {

	}
	else if (actionName == "centerAndSize") {
		if (winDelegate == nullptr) winDelegate = getWindowDelegateById(message);
		winDelegate->centerAndSize(message);
	}
	else if (actionName == "positionAndSize") {
		if (winDelegate == nullptr) winDelegate = getWindowDelegateById(message);
		winDelegate->positionAndSize(message);
	}
	else if (actionName == "getBound") {
		if (winDelegate == nullptr) winDelegate = getWindowDelegateById(message);
		auto rect = winDelegate->win->GetBounds();
		backMsg["result"] = {
			{"x",rect.x},
			{"y",rect.y},
			{"width",rect.width},
			{"height",rect.height}
		};
	}
	returnMessage(backMsg, message);
}

void WindowRouter::removeWindow(WindowDelegate* tar) {
	int index = -1;
	for (int i = 0; i < windows.size(); i++) {
		if (windows.at(i).get() == tar) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		//todo error
		return;
	}
	windows.erase(windows.begin()+index);
}