#include "BrowserProcessHandler.h"
#include "include/wrapper/cef_helpers.h"
#include "MessageProcessor/PageHandler.h"
#include "MessageRouter/ViewRouter.h"
#include "MessageRouter/WindowRouter.h"

//todo ʹ��ϵͳ���������ϵͳ����
//todo log�ļ�����ҳ�����־Ҳ�����
BrowserProcessHandler::~BrowserProcessHandler() {
    PageHandler::getInstance() = nullptr;
    ViewRouter::getInstance() = nullptr;
    WindowRouter::getInstance() = nullptr;
    WebSocketClient::getInstance() = nullptr;
}
/// <summary>
/// CEF�����������Ļ�����ʼ���ɹ�
/// </summary>
void BrowserProcessHandler::OnContextInitialized() {
    //��һ���µ��߳�������websocket�ͻ���
    auto websocketClient = WebSocketClient::getInstance();
    websocketClient->run();
    CEF_REQUIRE_UI_THREAD();
}
