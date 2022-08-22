#include <windows.h>
#include <boost/process.hpp>
#include <iostream>
#include "App.h"
#include "json/json.hpp"
#include "Config.h"
namespace bp = boost::process;



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
        // 只有这么一个数据时通过这种形式返回的，这个数据返回之后意味着Node的HTTP服务和WebSocket服务已经成功启动了
        nlohmann::json msg = nlohmann::json::parse(line);
        auto msgName = msg["name"].get<std::string>();
        if (msgName == "backendPort") {
            // 开发者可以指定端口，但如果开发者指定的端口被占用，那么还是会随机搞一个端口
            Config::get()["backendPort"] = msg["name"];
            break;
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
    std::thread nodeThread = std::thread(startNodeProcess);
    nodeThread.join();
    CefRefPtr<App> app(new App());
    CefInitialize(main_args, settings, app.get(), nullptr);
    CefRunMessageLoop();
    CefShutdown();
    return 0;
}