#pragma once
#include <malloc.h>
#include <locale>
#include <codecvt>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>

typedef websocketpp::client<websocketpp::config::asio_client> client;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;
class WebSocketClient
{
public:
    WebSocketClient() = default;
    void terminate();
    WebSocketClient(const WebSocketClient&) = delete;
    WebSocketClient& operator=(const WebSocketClient&) = delete;
    void run();
    void sendMessage(std::string& message);
    static WebSocketClient* getInstance();
private:
    void onMessage(websocketpp::connection_hdl hdl, message_ptr msg);
    void listen();
    client client;
    client::connection_ptr conn;
    std::thread* wsThread = nullptr;
};

