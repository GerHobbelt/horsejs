#include "WebSocketClient.h"
#include "include/cef_app.h"
#include "include/wrapper/cef_helpers.h"
#include "include/base/cef_callback.h"
#include "include/cef_task.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/base/cef_logging.h"
#include "../Config.h"
#include "MessageRouter/WindowRouter.h"
#include "MessageRouter/ViewRouter.h"
#include "../json/json.hpp"
using nlohmann::json;
using websocketpp::lib::bind;

namespace {
    CefRefPtr<WebSocketClient> instance = nullptr;
}
CefRefPtr<WebSocketClient> WebSocketClient::getInstance() {
    if (instance == nullptr) {
        instance = new WebSocketClient();
    }
    return instance;
}
WebSocketClient::~WebSocketClient() {
    client.close(conn->get_handle(), 0, "app exit");
    if (wsThread != nullptr) {
        wsThread->join();
    }
    delete wsThread;
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
        LOG(0) << "websocket connect error:" << ec.message();
        return;
    }
    // 这里只是请求建立连接，服务端收不到任何消息
    client.connect(conn);
    // 这里是阻塞的，当连接断开后，阻塞终止
    client.run();
}
void WebSocketClient::run() {
    wsThread = new std::thread(&WebSocketClient::listen, this);
}
void WebSocketClient::onMessage(websocketpp::connection_hdl hdl, message_ptr msg) {
    auto msgStr = msg->get_payload();
    LOG(INFO) << "msg from backend" << msgStr;
    json message = json::parse(msgStr);
    auto className = message["className"].get<std::string>();
    if (className == "Window") {
        auto windowRouter = WindowRouter::getInstance();
        CefPostTask(TID_UI, base::BindOnce(&WindowRouter::routeMessage, windowRouter,message,nullptr));
    }
    else if (className == "View") {
        auto viewRouter = ViewRouter::getInstance();
        CefPostTask(TID_UI, base::BindOnce(&ViewRouter::routeMessage, viewRouter, message));
    }
    //std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    //std::wstring msgStr = converter.from_bytes(msg->get_payload());
    //std::wstring testMsg = L"这是我的消息";
    //std::string narrow = converter.to_bytes(testMsg);
    //sendMessage(narrow);
}
void WebSocketClient::sendMessage(std::string& message) {
    //跨线程发送消息，没任何问题
    websocketpp::lib::error_code ec;
    client.send(conn->get_handle(), message, websocketpp::frame::opcode::text, ec);
    if (ec) {
        LOG(0)<<"websocket message send error:" << ec.message();
    }
}
void WebSocketClient::terminate() {
    //关闭连接，等待线程退出
    client.close(conn->get_handle(), 0, "app exit");
    if (wsThread != nullptr) {
        wsThread->join();
    }
    delete wsThread;
    instance = nullptr;
}
