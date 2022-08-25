#include "WebSocketClient.h"
#include "include/base/cef_logging.h"
#include "Config.h"

using websocketpp::lib::bind;

void WebSocketClient::listen() {
    std::string uri = config["backendWebSocketServer"].get<std::string>();
    if (uri.find("?") == std::string::npos) {
        uri += "?client=browser";
    }
    else {
        uri += "&client=browser";
    }
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
    // 这里只是请求建立连接，服务端收不到任何消息
    c.connect(conn);
    // 这里是阻塞的，当连接断开后，阻塞终止
    c.run();
}
void WebSocketClient::run() {
    std::unique_lock<std::mutex> lck(mtx);
    wsThread = new std::thread(&WebSocketClient::listen, this);
    //开始阻塞，只有收到第一条消息后，阻塞才终止
    cv.wait(lck);
}
void WebSocketClient::onMessage(websocketpp::connection_hdl hdl, message_ptr msg) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring msgStr = converter.from_bytes(msg->get_payload());
    LOG(INFO) << "websocket msg" << msgStr;
    if (msgStr == L"hi") {
        //收到服务端发来的第一条消息后，主线程的阻塞才终止
        cv.notify_one();
    }
    //std::wstring testMsg = L"这是我的消息";
    //std::string narrow = converter.to_bytes(testMsg);
    //sendMessage(narrow);
    //todo 接下去就要路由消息到具体的业务处理单元了
    

}
void WebSocketClient::sendMessage(std::string& message) {
    websocketpp::lib::error_code ec;
    c.send(conn->get_handle(), message, websocketpp::frame::opcode::text, ec);
    if (ec) {
        std::cout << "Echo failed because: " << ec.message() << std::endl;
    }
}
void WebSocketClient::terminate() {
    //关闭连接，等待线程退出
    c.close(conn->get_handle(), 0, "app exit");
    wsThread->join();
}
