#include "BrowserProcessHandler.h"
#include "include/wrapper/cef_helpers.h"
//#include "MessageProcessor/Window/WindowDelegate.h"
//#include "../json/json.hpp"

BrowserProcessHandler::BrowserProcessHandler(std::string& port) {
    //初始化全局config
    Config::init();
    if (port != "") {
        config["httpAndWebSocketServicePort"] = port;
    }
    //在一个新的线程里启动websocket客户端
    auto websocketClient = WebSocketClient::getInstance();
    websocketClient->run();
}
/// <summary>
/// CEF主进程上下文环境初始化成功
/// </summary>
void BrowserProcessHandler::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();
    //std::string jsonStr = R"({"with":800,"height":600,"x":100,"y":100,"position":"centerDesktop","frameless":true,"layout":"default","url":"https://www.baidu.com"})";
    //auto obj = nlohmann::json::parse(jsonStr);
    //CefWindow::CreateTopLevelWindow(new WindowDelegate(obj));
}
/// <summary>
/// 关闭websocket线程，不然应用退出会有异常
/// </summary>
BrowserProcessHandler::~BrowserProcessHandler() {
    auto websocketClient = WebSocketClient::getInstance();
    websocketClient->terminate();
}