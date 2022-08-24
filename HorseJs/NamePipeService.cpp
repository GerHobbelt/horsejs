#include "NamePipeService.h"
#include <iostream>
#include <boost/process.hpp>
#include <boost/asio.hpp>
#include "json/json.hpp"
#include "Config.h"
#include <mutex>
#include <condition_variable>

namespace NamePipeService {
    namespace bp = boost::process;
    namespace asio = boost::asio;
    std::mutex              g_mutex;     // 用到的全局锁
    std::condition_variable g_cond;      // 用到的条件变量
    
    void _startNamePipeService() {
#ifdef WIN32
        std::string pipeName = R"(\\.\pipe\horsepipe)";
#else
        pipeName = "/tmp/unix.sock",
#endif // WIN32
        asio::io_service ios;
        bp::async_pipe pipe(ios, pipeName);
        asio::streambuf buf;
        std::string read_string;
        auto d_buffer = boost::asio::dynamic_buffer(read_string);
        auto onData = [&](const boost::system::error_code& ec, size_t n) {
            std::cout << "I'm reading " << n << " characters from the child process. Can't wait for more!" << std::endl;
            d_buffer.consume(d_buffer.size());
            ios.poll();
            ios.restart();
        };
        boost::asio::async_read_until(pipe, d_buffer, '\n', onData);
            //if (size != 0) {
            //    boost::asio::streambuf::const_buffers_type cbt = buf.data();
            //    std::string jsonStr(boost::asio::buffers_begin(cbt), boost::asio::buffers_end(cbt));
            //    // 只有这么一个数据时通过这种形式返回的，这个数据返回之后意味着Node的HTTP服务和WebSocket服务已经成功启动了
            //    nlohmann::json msg = nlohmann::json::parse(jsonStr);
            //    auto msgName = msg["name"].get<std::string>();
            //    if (msgName == "backendLocalServiceAddress") {
            //        // 开发者可以指定端口，但如果开发者指定的端口被占用，那么还是会随机搞一个端口
            //        auto config = Config::get();
            //        config["backendHttpService"] = msg["httpAddress"].get<std::string>();
            //        config["backendWebSocketService"] = msg["websocketAddress"].get<std::string>();
            //        g_cond.notify_one();
            //    }
            //}
            //else {
            //    throw ec.what();
            //}
        //});
         ios.run();
    }
    void startNamePipeService() {
        std::thread serviceThread(_startNamePipeService);
        std::unique_lock<std::mutex> lock(g_mutex);
        g_cond.wait(lock);
    }
}