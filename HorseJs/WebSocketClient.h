#pragma once
#include <malloc.h>
#include <locale>
#include <codecvt>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

typedef websocketpp::client<websocketpp::config::asio_client> client;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;
class WebSocketClient : public std::enable_shared_from_this<WebSocketClient>
{
public:
    WebSocketClient() = default;
    WebSocketClient(const WebSocketClient&) = delete;
    WebSocketClient& operator=(const WebSocketClient&) = delete;
    void run();
private:
    void onMessage(client* c, websocketpp::connection_hdl hdl, message_ptr msg);
    void listen();
    std::thread* wsThread;
    std::mutex mtx;
    std::condition_variable cv;
};

