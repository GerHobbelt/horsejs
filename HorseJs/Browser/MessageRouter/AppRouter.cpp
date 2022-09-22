#include "AppRouter.h"
#include "include/cef_version.h"
#include "../WebSocketClient.h"
namespace {
	CefRefPtr<AppRouter> instance = nullptr;
}

CefRefPtr<AppRouter> AppRouter::getInstance() {
	if (!instance) {
		instance = new AppRouter();
	}
	return instance;
}

void AppRouter::routeMessage(const nlohmann::json& message, bool isFromNodeProcess, nlohmann::json& result, CefRefPtr<CefFrame> frame) {
	auto actionName = message["__actionName"].get<std::string>();
	if (actionName == "getVersionInfo") {
		result["horseJsVersion"] = { 0,0,12 };
		result["cefVersion"] = { CEF_VERSION_MAJOR ,CEF_VERSION_MINOR ,CEF_VERSION_PATCH ,CEF_COMMIT_NUMBER };
		result["chromeVersion"] = { CHROME_VERSION_MAJOR ,CHROME_VERSION_MINOR ,CHROME_VERSION_BUILD ,CHROME_VERSION_PATCH };
	}
	if (isFromNodeProcess) {
		WebSocketClient::getInstance()->sendMessage(result);
	}
	else {
		std::string resultStr = result.dump();
		CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(resultStr);
		frame->SendProcessMessage(PID_RENDERER, msg);
	}
}