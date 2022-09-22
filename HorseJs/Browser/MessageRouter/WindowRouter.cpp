#include "WindowRouter.h"
#include "../WebSocketClient.h"
#include "include/views/cef_window.h"
#include "include/views/cef_browser_view.h"
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
CefRefPtr<WindowDelegate> WindowRouter::getWindowDelegateById(int winId){
	int index = -1;
	for (int i = 0; i < windows.size(); i++) {
		if (windows.at(i)->win->GetID() == winId) {
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

void WindowRouter::routeMessage(const nlohmann::json& message,bool isFromNodeProcess, nlohmann::json&  result, CefRefPtr<CefFrame> frame) {
	auto actionName = message["__actionName"].get<std::string>();
	if (actionName == "createWindow") {
		auto winId = windows.size();
		CefRefPtr<WindowDelegate> winDelegate = new WindowDelegate(message, winId);
		windows.push_back(winDelegate);
		result["winId"] = winId;
		result["viewId"] = winDelegate->view->GetID();
	}
	else {
		auto winId = message["__winId"].get<int>();
		CefRefPtr<WindowDelegate> winDelegate = this->getWindowDelegateById(winId);
		if (actionName == "addOverlayView") {
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
			auto viewId = message["viewId"].get<int>();
			winDelegate->removeView(viewId);
		}
		else if (actionName == "setVisible") {
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
			winDelegate->centerAndSize(message);
		}
		else if (actionName == "positionAndSize") {
			winDelegate->positionAndSize(message);
		}
		else if (actionName == "getBound") {
			auto rect = winDelegate->win->GetBounds();
			result["result"] = {
				{"x",rect.x},
				{"y",rect.y},
				{"width",rect.width},
				{"height",rect.height}
			};
		}
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