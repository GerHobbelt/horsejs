#include "BrowserProcessHandler.h"
#include "include/wrapper/cef_helpers.h"
#include "MessageProcessor/PageHandler.h"
#include "MessageRouter/ViewRouter.h"
#include "MessageRouter/WindowRouter.h"
//#include "../json/json.hpp"

//todo ʹ��ϵͳ���������ϵͳ����
//todo log�ļ�����ҳ�����־Ҳ�����
BrowserProcessHandler::~BrowserProcessHandler() {
    PageHandler::getInstance() = nullptr;
    ViewRouter::getInstance() = nullptr;
    WindowRouter::getInstance() = nullptr;
    WebSocketClient::getInstance() = nullptr;
}
BrowserProcessHandler::BrowserProcessHandler(std::string& port) {
    //��ʼ��ȫ��config
    Config::init();
    if (port != "") {
        config["httpAndWebSocketServicePort"] = port;
    }
    //��һ���µ��߳�������websocket�ͻ���
    auto websocketClient = WebSocketClient::getInstance();
    websocketClient->run();
}
/// <summary>
/// CEF�����������Ļ�����ʼ���ɹ�
/// </summary>
void BrowserProcessHandler::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();
}
