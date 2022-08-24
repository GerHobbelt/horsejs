#include "WebSocketClient.h"
#include "include/base/cef_logging.h"

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

WebSocketClient::WebSocketClient() {

}
void WebSocketClient::listen() {
    std::string uri = "ws://localhost:5916";
    client c;
    //c.set_access_channels(websocketpp::log::alevel::all);
    //c.clear_access_channels(websocketpp::log::alevel::frame_payload);
    // Initialize ASIO
    c.init_asio();
    // Register our message handler
    c.set_message_handler(bind(&WebSocketClient::onMessage, this, &c, ::_1, ::_2));
    websocketpp::lib::error_code ec;
    client::connection_ptr con = c.get_connection(uri, ec);
    if (ec) {
        std::cout << "could not create connection because: " << ec.message() << std::endl;
        return;
    }
    // Note that connect here only requests a connection. No network messages are
    // exchanged until the event loop starts running in the next line.
    c.connect(con);
    // Start the ASIO io_service run loop
    // this will cause a single connection to be made to the server. c.run()
    // will exit when this connection is closed.
    c.run();
}
void WebSocketClient::run() {
    std::unique_lock<std::mutex> lck(mtx_syn);
    wsThread = new std::thread(&WebSocketClient::listen, this);
    cv_syn.wait(lck);
}
void WebSocketClient::onMessage(client* c, websocketpp::connection_hdl hdl, message_ptr msg) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring msgStr = converter.from_bytes(msg->get_payload());
    LOG(INFO) << "websocket msg" << msgStr;
    cv_syn.notify_one();
    websocketpp::lib::error_code ec;
    c->send(hdl, msg->get_payload(), msg->get_opcode(), ec);
    if (ec) {
        std::cout << "Echo failed because: " << ec.message() << std::endl;
    }
}
