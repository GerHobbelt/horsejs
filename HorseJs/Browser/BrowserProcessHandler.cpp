#include "BrowserProcessHandler.h"
#include "include/wrapper/cef_helpers.h"
#include "MessageProcessor/PageHandler.h"
#include "MessageRouter/ViewRouter.h"
#include "MessageRouter/WindowRouter.h"
//#include "../json/json.hpp"

//todo 使用系统代理或不试用系统代理
//todo log的级别，网页里的日志也会输出
BrowserProcessHandler::~BrowserProcessHandler() {
    PageHandler::getInstance() = nullptr;
    ViewRouter::getInstance() = nullptr;
    WindowRouter::getInstance() = nullptr;
    WebSocketClient::getInstance() = nullptr;
}
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
}
