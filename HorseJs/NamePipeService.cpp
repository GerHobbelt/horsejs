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
    std::mutex              g_mutex;     // �õ���ȫ����
    std::condition_variable g_cond;      // �õ�����������
    
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
            //    // ֻ����ôһ������ʱͨ��������ʽ���صģ�������ݷ���֮����ζ��Node��HTTP�����WebSocket�����Ѿ��ɹ�������
            //    nlohmann::json msg = nlohmann::json::parse(jsonStr);
            //    auto msgName = msg["name"].get<std::string>();
            //    if (msgName == "backendLocalServiceAddress") {
            //        // �����߿���ָ���˿ڣ������������ָ���Ķ˿ڱ�ռ�ã���ô���ǻ������һ���˿�
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