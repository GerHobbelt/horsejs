#include <windows.h>
#include <boost/process.hpp>
#include <iostream>
#include "App.h"
#include "json/json.hpp"
namespace bp = boost::process;


int backendPort = -1;

/// <summary>
/// 启动Node进程
/// 要接收Node进程传过来的数据（webserver的端口号）
/// 这个过程是阻塞的，所以开了个新线程来做这个事情
/// </summary>
void startNodeProcess() {
    bp::ipstream std_stream;
    auto dir = bp::start_dir("D:\\project\\horsejs\\HorseJs\\backend\\debug");
    bp::group g;
    bp::child c("D:\\sdk\\node\\Debug\\node.exe", "index.js", dir, g, bp::std_out > std_stream);
    std::string line;
    while (std_stream && std::getline(std_stream, line) && !line.empty()) {
        // 最好把这玩意儿封装成一个对象
        // 消费者可以向这个对象注册回调函数
        // 回调函数被放置在这个对象一个map里面
        // 收到的msg.name就是map里面的key
        // 这样收到一个msg，就可以调用消费者注册来的回调函数了
        // 而且msg的value可以作为参数传递给回调函数
        nlohmann::json msg = nlohmann::json::parse(line);
        auto msgName = msg["name"].get<std::string>();
        if (msgName == "backendPort") {
            backendPort = msg["value"].get<int>();
        }
    }
    //应用重启，或者重启Node进程
}

//整个应用的入口函数
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    CefEnableHighDPISupport();
    CefMainArgs main_args(hInstance);
    CefSettings settings;
    int exit_code = CefExecuteProcess(main_args, nullptr, nullptr);
    if (exit_code >= 0) {
        return exit_code;
    }
    std::thread th1;
    th1 = std::thread(startNodeProcess);
    while (backendPort == -1)
    {
        //wait
    }
    CefRefPtr<App> app(new App());
    CefInitialize(main_args, settings, app.get(), nullptr);
    CefRunMessageLoop();
    th1.detach();
    CefShutdown();
    return 0;
}