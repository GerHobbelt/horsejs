#include "MessageRouter.h"
#include "include/cef_app.h"
#include "include/wrapper/cef_helpers.h"
#include "include/base/cef_callback.h"
#include "include/cef_task.h"
#include "include/wrapper/cef_closure_task.h"
#include "MessageRouter/WindowRouter.h"
#include "MessageRouter/ViewRouter.h"
namespace MessageRouter {	
	void route(const nlohmann::json& message) {
		auto className = message["className"].get<std::string>();
		if (className == "Window") {
			auto actionName = message["actionName"].get<std::string>();
			auto windowRouter = WindowRouter::getInstance();
			if (actionName == "createWindow") {
				//要让主线程做这个工作
				CefPostTask(TID_UI, base::BindOnce(&WindowRouter::createWindow, windowRouter, message));
			}
			else if (actionName == "addView") {
				CefPostTask(TID_UI, base::BindOnce(&WindowRouter::addView, windowRouter, message));
			}
			else if (actionName == "hideAllView") {

			}
			else if (actionName == "removeView") {

			}
			else if (actionName == "hide") {
				CefPostTask(TID_UI, base::BindOnce(&WindowRouter::hide, windowRouter , message));
			}
			else if (actionName == "show") {
				CefPostTask(TID_UI, base::BindOnce(&WindowRouter::show, windowRouter, message));
			}
			else if (actionName == "setTitle") {

			}
			else if (actionName == "resize") {

			}
			else if (actionName == "center") {

			}
		}
		else if (className == "View") {
			auto actionName = message["actionName"].get<std::string>();
			auto viewRouter = ViewRouter::getInstance();
			if (actionName == "setVisible") {
				CefPostTask(TID_UI, base::BindOnce(&ViewRouter::setVisible, viewRouter, message));
			}
			else if (actionName == "openDevTools") {
				CefPostTask(TID_UI, base::BindOnce(&ViewRouter::openDevTools, viewRouter, message));
			}
		}
	}
}