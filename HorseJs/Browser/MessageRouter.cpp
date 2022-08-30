#include "MessageRouter.h"
#include "include/cef_app.h"
#include "include/wrapper/cef_helpers.h"
#include "include/base/cef_callback.h"
#include "include/cef_task.h"
#include "include/wrapper/cef_closure_task.h"
#include "MessageProcessor/Window/WindowDelegate.h"
namespace MessageRouter {
	void route(const nlohmann::json& message) {
		auto className = message["className"].get<std::string>();
		if (className == "Window") {
			auto actionName = message["actionName"].get<std::string>();
			if (actionName == "createWindow") {	
				//要让主线程做这个工作
				CefPostTask(TID_UI, base::BindOnce(&MessageRouter::createWindow, message["params"]));
				//CefTaskRunner
			}
			else if (actionName == "contextMenu") {

			}			
		}
	}
	void createWindow(const nlohmann::json& params) {
		auto windowDelegate = new WindowDelegate(params);
		CefWindow::CreateTopLevelWindow(windowDelegate);
	}
}