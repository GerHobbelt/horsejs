#include "WebSocketClient.h"
#include "include/base/cef_logging.h"
#include "../Config.h"
#include "MessageRouter.h"
#include "../json/json.hpp"
using nlohmann::json;
using websocketpp::lib::bind;

namespace {
    WebSocketClient* instance = nullptr;
}
WebSocketClient* WebSocketClient::getInstance() {
    if (instance == nullptr) {
        instance = new WebSocketClient();
    }
    return instance;
}
void WebSocketClient::listen() {
    std::string port = config["httpAndWebSocketServicePort"].get<std::string>();
    auto uri = "ws://localhost:" + port + "/?client=browser";
    //c.set_access_channels(websocketpp::log::alevel::all);
    //c.clear_access_channels(websocketpp::log::alevel::frame_payload);
    client.init_asio();
    client.set_message_handler(bind(&WebSocketClient::onMessage, this, websocketpp::lib::placeholders::_1, websocketpp::lib::placeholders::_2));
    websocketpp::lib::error_code ec;
    conn = client.get_connection(uri, ec);
    if (ec) {
        LOG(0) << "websocket connect error" << ec.message();
        return;
    }
    // ����ֻ�����������ӣ�������ղ����κ���Ϣ
    client.connect(conn);
    // �����������ģ������ӶϿ���������ֹ
    client.run();
}
void WebSocketClient::run() {
    wsThread = new std::thread(&WebSocketClient::listen, this);
}
void WebSocketClient::onMessage(websocketpp::connection_hdl hdl, message_ptr msg) {
    auto msgStr = msg->get_payload();
    LOG(INFO) << "msg from backend" << msgStr;
    json msgObj = json::parse(msgStr);
    MessageRouter::route(msgObj);
    //std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    //std::wstring msgStr = converter.from_bytes(msg->get_payload());


    
    //todo ����ȥ��Ҫ·����Ϣ�������ҵ����Ԫ��
    

    //std::wstring testMsg = L"�����ҵ���Ϣ";
    //std::string narrow = converter.to_bytes(testMsg);
    //sendMessage(narrow);
}
void WebSocketClient::sendMessage(std::string& message) {
    //todo ���̷߳�����Ϣ
    websocketpp::lib::error_code ec;
    client.send(conn->get_handle(), message, websocketpp::frame::opcode::text, ec);
    if (ec) {
        std::cout << "Echo failed because: " << ec.message() << std::endl;
    }
}
void WebSocketClient::terminate() {
    //�ر����ӣ��ȴ��߳��˳�
    client.close(conn->get_handle(), 0, "app exit");
    if (wsThread != nullptr) {
        wsThread->join();
    }
    delete wsThread;
    delete instance;
    instance = nullptr;
}
