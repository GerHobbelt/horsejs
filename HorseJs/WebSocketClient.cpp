#include "WebSocketClient.h"
#include "include/base/cef_logging.h"
#include "Config.h"

using websocketpp::lib::bind;

void WebSocketClient::listen() {
    std::string port = config["httpAndWebSocketServicePort"].get<std::string>();
    auto uri = "ws://localhost:" + port + "/?client=browser";
    //c.set_access_channels(websocketpp::log::alevel::all);
    //c.clear_access_channels(websocketpp::log::alevel::frame_payload);
    c.init_asio();
    c.set_message_handler(bind(&WebSocketClient::onMessage, this, websocketpp::lib::placeholders::_1, websocketpp::lib::placeholders::_2));
    websocketpp::lib::error_code ec;
    conn = c.get_connection(uri, ec);
    if (ec) {
        LOG(0) << "websocket connect error" << ec.message();
        return;
    }
    // ����ֻ�����������ӣ�������ղ����κ���Ϣ
    c.connect(conn);
    // �����������ģ������ӶϿ���������ֹ
    c.run();
}
void WebSocketClient::run() {
    wsThread = new std::thread(&WebSocketClient::listen, this);
}
void WebSocketClient::onMessage(websocketpp::connection_hdl hdl, message_ptr msg) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring msgStr = converter.from_bytes(msg->get_payload());
    LOG(INFO) << "websocket msg" << msgStr;
    //todo ����ȥ��Ҫ·����Ϣ�������ҵ����Ԫ��
    

    //std::wstring testMsg = L"�����ҵ���Ϣ";
    //std::string narrow = converter.to_bytes(testMsg);
    //sendMessage(narrow);
}
void WebSocketClient::sendMessage(std::string& message) {
    websocketpp::lib::error_code ec;
    c.send(conn->get_handle(), message, websocketpp::frame::opcode::text, ec);
    if (ec) {
        std::cout << "Echo failed because: " << ec.message() << std::endl;
    }
}
void WebSocketClient::terminate() {
    //�ر����ӣ��ȴ��߳��˳�
    if (c.is_listening()) {
        c.close(conn->get_handle(), 0, "app exit");
    }
    if (wsThread != nullptr) {        
        wsThread->join();
    }
}
