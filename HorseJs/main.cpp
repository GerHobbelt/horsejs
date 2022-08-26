#include <windows.h>
#include "App.h"
#include "json/json.hpp"
#include "Config.h"
#include "Renderer.h"
#include "Other.h"
#include "WebSocketClient.h"

//整个应用的入口函数
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    CefEnableHighDPISupport();
    //收集命令行参数
    CefMainArgs main_args(hInstance);
    CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
    command_line->InitFromString(::GetCommandLineW());
    //为不同进程创建不同的处理对象
    CefRefPtr<CefApp> app;
    WebSocketClient wsClient;
    if (!command_line->HasSwitch("type")) {
        Config::init();
        if (command_line->HasSwitch("horse-port")) {
            config["httpAndWebSocketServicePort"] = command_line->GetSwitchValue("horse-port").ToString();
        }        
        //启动websocket客户端
        wsClient.run();
        app = new App();
    }
    else if (command_line->GetSwitchValue("type").ToString() == "renderer") {
        //--renderer-startup-dialog
        app = new Renderer();
    }
    else {
        app = new Other();
    }
    //启动子进程
    int exit_code = CefExecuteProcess(main_args, app, nullptr);
    if (exit_code >= 0) {
        return exit_code;
    }
    //CEF消息循环
    CefSettings settings;
    CefInitialize(main_args, settings, app.get(), nullptr);
    CefRunMessageLoop();
    wsClient.terminate();
    CefShutdown();
    return 0;
}