#include "WindowRouter.h"
#include "../WebSocketClient.h"
#include "include/views/cef_window.h"
#include "include/views/cef_browser_view.h"

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

void WindowRouter::routeMessage(const nlohmann::json& message, CefRefPtr<WindowDelegate> winDelegate, nlohmann::json& result) {
	auto actionName = message["__actionName"].get<std::string>();
	if (actionName == "createWindow") {
		auto winId = windows.size();
		CefRefPtr<WindowDelegate> winDelegate = new WindowDelegate(message, winId);
		windows.push_back(winDelegate);
		result["winId"] = winId;
		result["viewId"] = winDelegate->view->GetID();
	}
	else if (actionName == "addOverlayView") {
		if (winDelegate == nullptr) winDelegate = getWindowDelegateById(message);
		auto viewId = winDelegate->AddOverlayView(message);
		result["winId"] = winDelegate->win->GetID();
		result["viewId"] = viewId;
	}
	else if (actionName == "getCurrentWindow") {
		//这个方法只为渲染进程服务，所以winDelegate必然存在
		result["winId"] = winDelegate->win->GetID();
		result["viewId"] = winDelegate->view->GetID();
	}
	else if (actionName == "hideAllView") {

	}
	else if (actionName == "removeView") {
		if (winDelegate == nullptr) winDelegate = getWindowDelegateById(message);
		auto viewId = message["viewId"].get<int>();
		winDelegate->removeView(viewId);
	}
	else if (actionName == "setVisible") {
		if (winDelegate == nullptr) winDelegate = getWindowDelegateById(message);
		auto visible = message["visible"].get<bool>();
		if (visible) {
			winDelegate->win->Show();
		}
		else {
			winDelegate->win->Hide();
		}
	}
	else if (actionName == "setTitle") {
		auto title = message["title"].get<std::string>();
		winDelegate->win->SetTitle(title);
	}
	else if (actionName == "minimize") {
		winDelegate->win->Minimize();
	}
	else if (actionName == "maximize") {
		winDelegate->win->Maximize();
	}
	else if (actionName == "restore") {
		winDelegate->win->Restore();
	}
	else if (actionName == "close") {
		winDelegate->win->Close();
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
		result["result"] = {
			{"x",rect.x},
			{"y",rect.y},
			{"width",rect.width},
			{"height",rect.height}
		};
	}
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