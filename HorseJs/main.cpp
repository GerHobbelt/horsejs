#include <malloc.h>
#include <windows.h>
#include <filesystem>
#include <boost/process.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <fstream>
#include "App.h"
#include "json/json.hpp"
#include "Config.h"
#include "Renderer.h"
#include "Other.h"
#include "WebSocketClient.h"

namespace bp = boost::process;
namespace asio = boost::asio;
namespace fs = std::filesystem;
bp::child* nodeProcess;

void initConfig() {
    //todo 这个路径有问题
    auto configFile = fs::current_path().append("config.json");
    if (fs::exists(configFile)) {
        std::ifstream in(configFile);
        std::istreambuf_iterator<char> begin(in), end;
        std::string configStr(begin, end);
        config = nlohmann::json::parse(configStr);
    }
    else {
        //todo message box show win/mac
    }
}


fs::path getExeDir() {
    WCHAR _exePath[MAX_PATH];
    DWORD result = GetModuleFileName(NULL, _exePath, MAX_PATH);
    if (result == 0) {
        throw "Error in getting module filename.";
    }
    std::wstring exePathStr(_exePath);
    auto exePath = fs::path(exePathStr);
    return exePath.remove_filename();
}



/// <summary>
/// 启动Node进程
/// 要接收Node进程传过来的数据（webserver的端口号）
/// 这个过程是阻塞的，所以开了个新线程来做这个事情
/// </summary>
void startNodeProcess() {
    asio::io_service service;
    asio::ip::tcp::acceptor acceptor(service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 0));
    unsigned short port = acceptor.local_endpoint().port();
    //todo 在一个极短的时间内如果有一个其他进程占用了这个端口，将导致backend使用这个端口出现问题
    auto backendPath = getExeDir();
    auto nodePath = backendPath;
    auto cmd = nodePath.append("node\\horseNode.exe").wstring() + L" index.js " + std::to_wstring(port);
    auto workingDir = boost::process::start_dir(backendPath.append("backend").wstring());
    nodeProcess = new bp::child(cmd, workingDir);
    config["backendHttpService"] = "http://localhost:" + std::to_string(port);
    config["backendWebSocketService"] = "ws://localhost:" + std::to_string(port);
}

//整个应用的入口函数
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    CefEnableHighDPISupport();
    //收集命令行参数
    CefMainArgs main_args(hInstance);
    CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
    command_line->InitFromString(::GetCommandLineW());
    //启动子进程
    int exit_code = CefExecuteProcess(main_args, nullptr, nullptr);
    if (exit_code >= 0) {
        return exit_code;
    }
    //为不同进程创建不同的处理对象
    CefRefPtr<CefApp> app;
    WebSocketClient wsClient;
    if (!command_line->HasSwitch("type")) {
        initConfig();
        auto backendServerType = config["backendUseRemoteServerOrLocalServer"].get<std::string>();
        if (backendServerType == "LocalServer") {
            startNodeProcess();
        }
        wsClient.run();
        app = new App();
    }
    else if (command_line->GetSwitchValue("type").ToString() == "renderer") {
        app = new Renderer();
    }
    else {
        app = new Other();
    }
    //CEF消息循环
    CefSettings settings;
    CefInitialize(main_args, settings, app.get(), nullptr);
    CefRunMessageLoop();
    nodeProcess->terminate();
    CefShutdown();
    return 0;
}