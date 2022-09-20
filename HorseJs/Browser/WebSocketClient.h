#pragma once
#include <malloc.h>
#include <locale>
#include <codecvt>
#include "include/wrapper/cef_helpers.h"
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>
#include "../json/json.hpp"
using nlohmann::json;

typedef websocketpp::client<websocketpp::config::asio_client> client;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;
class WebSocketClient : public virtual CefBaseRefCounted
{
public:
    ~WebSocketClient();
    void terminate();
    WebSocketClient(const WebSocketClient&) = delete;
    WebSocketClient& operator=(const WebSocketClient&) = delete;
    void run();
    void sendMessage(json& message);
    static CefRefPtr<WebSocketClient> getInstance();
private:
    IMPLEMENT_REFCOUNTING(WebSocketClient);
    WebSocketClient() = default;
    void onMessage(websocketpp::connection_hdl hdl, message_ptr msg);
    void listen();
    client client;
    client::connection_ptr conn;
    std::thread* wsThread = nullptr;
};

