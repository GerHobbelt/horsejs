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
				CefPostTask(TID_UI, base::BindOnce(&WindowRouter::createWindow, windowRouter, message));
			}
			else if (actionName == "addView") {
				CefPostTask(TID_UI, base::BindOnce(&WindowRouter::addView, windowRouter, message));
			}
			else if (actionName == "hideAllView") {

			}
			else if (actionName == "removeView") {
				CefPostTask(TID_UI, base::BindOnce(&WindowRouter::removeView, windowRouter, message));
			}
			else if (actionName == "setVisible") {
				CefPostTask(TID_UI, base::BindOnce(&WindowRouter::setVisible, windowRouter , message));
			}
			else if (actionName == "setTitle") {

			}
			else if (actionName == "centerAndSize") {
				CefPostTask(TID_UI, base::BindOnce(&WindowRouter::centerAndSize, windowRouter, message));
			}
			else if (actionName == "positionAndSize") {
				CefPostTask(TID_UI, base::BindOnce(&WindowRouter::positionAndSize, windowRouter, message));
			}
			else if (actionName == "getBound") {
				CefPostTask(TID_UI, base::BindOnce(&WindowRouter::getBound, windowRouter, message));
			}
		}
		else if (className == "View") {
			auto actionName = message["actionName"].get<std::string>();
			auto viewRouter = ViewRouter::getInstance();
			if (actionName == "setVisible") {
				CefPostTask(TID_UI, base::BindOnce(&ViewRouter::setVisible, viewRouter, message));
			}
			else if (actionName == "devTools") {
				CefPostTask(TID_UI, base::BindOnce(&ViewRouter::openDevTools, viewRouter, message));
			}
		}
	}
}