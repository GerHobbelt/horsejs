#include "MessageRouter.h"
#include "include/cef_app.h"
#include "include/wrapper/cef_helpers.h"
#include "include/base/cef_callback.h"
#include "include/cef_task.h"
#include "include/wrapper/cef_closure_task.h"
#include "MessageProcessor/WindowDelegate.h"
#include "MessageProcessor/Window/WindowMultiViewDelegate.h"
#include "MessageProcessor/Window/WindowOverlayViewDelegate.h"
#include "WebSocketClient.h"
namespace MessageRouter {
	std::vector<WindowDelegate*> windowDelegateVector;
	void createWindow(const nlohmann::json& message) {
		auto winDelegate = new WindowDelegate(message["params"]);
		windowDelegateVector.push_back(winDelegate);
		auto wsClient = WebSocketClient::getInstance();
		nlohmann::json backMsg = { {"__msgId", message["__msgId"].get<double>()} ,{"id",winDelegate->win->GetID()},};
		std::string msgStr = backMsg.dump();
		wsClient->sendMessage(msgStr);
	}
	void addViewOverlay(const nlohmann::json& message) {
		auto id = message["__winId"].get<int>();
		for (auto winDelegate : windowDelegateVector) {
			if (winDelegate->win->GetID() == id) {
				winDelegate->AddOverlayView(message["params"]);
				break;
			}			
		}
		auto wsClient = WebSocketClient::getInstance();
		nlohmann::json backMsg = { {"__msgId", message["__msgId"].get<double>()} };
		std::string msgStr = backMsg.dump();
		wsClient->sendMessage(msgStr);
	}
	void hideWindow(const nlohmann::json& message) {
		auto id = message["__winId"].get<int>();
		for (auto winDelegate : windowDelegateVector) {
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
	void showWindow(const nlohmann::json& message) {
		auto id = message["__winId"].get<int>();
		for (auto winDelegate : windowDelegateVector) {
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
	void createWindowMultiView(const nlohmann::json& params) {
		auto windowDelegate = new WindowMultiViewDelegate(params);
		CefWindow::CreateTopLevelWindow(windowDelegate);
	}
	void createWindowOverlayView(const nlohmann::json& params) {
		auto windowDelegate = new WindowOverlayViewDelegate(params);
		CefWindow::CreateTopLevelWindow(windowDelegate);
	}
	void route(const nlohmann::json& message) {
		auto className = message["className"].get<std::string>();
		if (className == "Window") {
			auto actionName = message["actionName"].get<std::string>();
			if (actionName == "createWindow") {	
				//要让主线程做这个工作
				CefPostTask(TID_UI, base::BindOnce(&createWindow, message));
			}
			else if (actionName == "addBrowserView") {
				CefPostTask(TID_UI, base::BindOnce(&addViewOverlay, message));
			}
			else if (actionName == "hide") {
				CefPostTask(TID_UI, base::BindOnce(&hideWindow, message));
			}
			else if (actionName == "show") {
				CefPostTask(TID_UI, base::BindOnce(&showWindow, message));
			}
			else if (actionName == "contextMenu") {

			}

/*			else if (actionName == "createWindowMultiView") {
				CefPostTask(TID_UI, base::BindOnce(&createWindowMultiView, message["params"]));
			}
			else if (actionName == "createWindowOverlayView") {
				CefPostTask(TID_UI, base::BindOnce(&createWindowOverlayView, message["params"]));
			}*/		
		}
	}
}