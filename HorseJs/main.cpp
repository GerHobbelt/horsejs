#include <windows.h>
#include "App.h"
#include "json/json.hpp"
#include "Config.h"
#include "Renderer.h"
#include "Other.h"
#include "WebSocketClient.h"
#include "NodeProcess.h"

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
    NodeProcess nodeProcess;
    if (!command_line->HasSwitch("type")) {
        Config::init();
        auto backendServerType = config["backendUseRemoteServerOrLocalServer"].get<std::string>();
        if (backendServerType == "localServer") {
            nodeProcess.run();
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
    wsClient.terminate();
    nodeProcess.terminate();
    CefShutdown();
    return 0;
}