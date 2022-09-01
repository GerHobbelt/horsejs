#include "BrowserProcessHandler.h"
#include "include/wrapper/cef_helpers.h"
//#include "MessageProcessor/Window/WindowDelegate.h"
//#include "../json/json.hpp"

//todo ʹ��ϵͳ���������ϵͳ����
//todo log�ļ�����ҳ�����־Ҳ�����
BrowserProcessHandler::~BrowserProcessHandler() {
    auto websocketClient = WebSocketClient::getInstance();
    websocketClient->terminate();
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
    //std::string jsonStr = R"({"with":800,"height":600,"x":100,"y":100,"position":"centerDesktop","frameless":true,"layout":"default","url":"https://www.baidu.com"})";
    //auto obj = nlohmann::json::parse(jsonStr);
    //CefWindow::CreateTopLevelWindow(new WindowDelegate(obj));
}
