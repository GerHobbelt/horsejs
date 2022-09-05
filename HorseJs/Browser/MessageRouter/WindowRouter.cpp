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

void WindowRouter::createWindow(const nlohmann::json& message) {
	auto winId = windows.size();
	CefRefPtr<WindowDelegate> winDelegate = new WindowDelegate(message["params"], winId);
	windows.push_back(winDelegate);
	auto wsClient = WebSocketClient::getInstance();
	//todo 好像释放不了？这个要验证一下
	nlohmann::json backMsg = { {"__msgId", message["__msgId"].get<double>()} ,{"id",winId}, };
	std::string msgStr = backMsg.dump();
	wsClient->sendMessage(msgStr);
}
void WindowRouter::addView(const nlohmann::json& message) {
	auto id = message["__winId"].get<int>();
	int viewId = -1;
	for (auto winDelegate : windows) {
		if (winDelegate->win->GetID() == id) {
			viewId = winDelegate->AddOverlayView(message["params"]);
			break;
		}
	}
	if (viewId == -1) {
		//todo send error back to end
	}
	auto wsClient = WebSocketClient::getInstance();
	nlohmann::json backMsg = { {"__msgId", message["__msgId"].get<double>()},{"id",viewId}, };
	std::string msgStr = backMsg.dump();
	wsClient->sendMessage(msgStr);
}
void WindowRouter::hide(const nlohmann::json& message) {
	auto id = message["__winId"].get<int>();
	for (auto winDelegate : windows) {
		if (winDelegate->win->GetID() == id) {
			winDelegate->win->Hide();
			break;
		}
	}
	auto wsClient = WebSocketClient::getInstance();
	nlohmann::json backMsg = { {"__msgId", message["__msgId"].get<double>()} };
	std::string msgStr = backMsg.dump();
	wsClient->sendMessage(msgStr);
}
void WindowRouter::show(const nlohmann::json& message) {
	auto id = message["__winId"].get<int>();
	for (auto winDelegate : windows) {
		if (winDelegate->win->GetID() == id) {
			winDelegate->win->Show();
			break;
		}
	}
	auto wsClient = WebSocketClient::getInstance();
	nlohmann::json backMsg = { {"__msgId", message["__msgId"].get<double>()} };
	std::string msgStr = backMsg.dump();
	wsClient->sendMessage(msgStr);
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
	if (windows.size() == 0) {
		CefQuitMessageLoop();
	}
}