#include "BrowserProcessHandler.h"
#include "include/wrapper/cef_helpers.h"
#include "MessageProcessor/PageHandler.h"
#include "MessageRouter/ViewRouter.h"
#include "MessageRouter/WindowRouter.h"

//todo 使用系统代理或不试用系统代理
//todo log的级别，网页里的日志也会输出
BrowserProcessHandler::~BrowserProcessHandler() {
    PageHandler::getInstance() = nullptr;
    ViewRouter::getInstance() = nullptr;
    WindowRouter::getInstance() = nullptr;
    WebSocketClient::getInstance() = nullptr;
}
/// <summary>
/// CEF主进程上下文环境初始化成功
/// </summary>
void BrowserProcessHandler::OnContextInitialized() {
    //在一个新的线程里启动websocket客户端
    auto websocketClient = WebSocketClient::getInstance();
    websocketClient->run();
    CEF_REQUIRE_UI_THREAD();
}
