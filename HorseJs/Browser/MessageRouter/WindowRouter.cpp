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

int WindowRouter::getWindowIndexById(int id) {
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
	return index;
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
	int winIndex = getWindowIndexById(id);
	int viewId = windows.at(winIndex)->AddOverlayView(message["params"]);
	auto wsClient = WebSocketClient::getInstance();
	nlohmann::json backMsg = { {"__msgId", message["__msgId"].get<double>()},{"id",viewId}, };
	std::string msgStr = backMsg.dump();
	wsClient->sendMessage(msgStr);
}
void WindowRouter::removeView(const nlohmann::json& message) {
	auto id = message["__winId"].get<int>();
	int winIndex = getWindowIndexById(id);
	auto viewId = message["params"]["viewId"].get<int>();
	windows.at(winIndex)->removeView(viewId);
	auto wsClient = WebSocketClient::getInstance();
	nlohmann::json backMsg = { {"__msgId", message["__msgId"].get<double>()} };
	std::string msgStr = backMsg.dump();
	wsClient->sendMessage(msgStr);
}
void WindowRouter::setVisible(const nlohmann::json& message) {
	auto id = message["__winId"].get<int>();
	int winIndex = getWindowIndexById(id);
	auto visible = message["params"]["visible"].get<bool>();
	if (visible) {
		windows.at(winIndex)->win->Show();
	}
	else
	{
		windows.at(winIndex)->win->Hide();
	}	
	auto wsClient = WebSocketClient::getInstance();
	nlohmann::json backMsg = { {"__msgId", message["__msgId"].get<double>()} };
	std::string msgStr = backMsg.dump();
	wsClient->sendMessage(msgStr);
}
void WindowRouter::centerAndSize(const nlohmann::json& message) {
	auto id = message["__winId"].get<int>();
	int winIndex = getWindowIndexById(id);
	windows.at(winIndex)->centerAndSize(message);
	auto wsClient = WebSocketClient::getInstance();
	nlohmann::json backMsg = { {"__msgId", message["__msgId"].get<double>()} };
	std::string msgStr = backMsg.dump();
	wsClient->sendMessage(msgStr);
}
void WindowRouter::positionAndSize(const nlohmann::json& message) {
	auto id = message["__winId"].get<int>();
	int winIndex = getWindowIndexById(id);
	windows.at(winIndex)->positionAndSize(message);
	auto wsClient = WebSocketClient::getInstance();
	nlohmann::json backMsg = { {"__msgId", message["__msgId"].get<double>()} };
	std::string msgStr = backMsg.dump();
	wsClient->sendMessage(msgStr);
}

void WindowRouter::getBound(const nlohmann::json& message) {
	auto id = message["__winId"].get<int>();
	int winIndex = getWindowIndexById(id);
	auto rect = windows.at(winIndex)->win->GetBounds();
	auto wsClient = WebSocketClient::getInstance();
	nlohmann::json backMsg = { 
		{"__msgId", message["__msgId"].get<double>()},
		{"result",{
			{"x",rect.x},
			{"y",rect.y},
			{"width",rect.width},
			{"height",rect.height}
		}}
	};
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
	//if (windows.size() == 0) {
	//	CefQuitMessageLoop();
	//}
}