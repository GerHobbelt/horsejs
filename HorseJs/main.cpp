#include <windows.h>
#include "Browser/BrowserProcessHandler.h"
#include "Render/RenderProcessHandler.h"
#include "Other/OtherProcessHandler.h"

//整个应用的入口函数
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    CefEnableHighDPISupport();
    //收集命令行参数
    CefMainArgs mainArgs(hInstance);
    CefRefPtr<CefCommandLine> commandLine = CefCommandLine::CreateCommandLine();
    commandLine->InitFromString(::GetCommandLineW());//todo mac
    //为不同进程创建不同的处理对象
    CefRefPtr<CefApp> app;    
    if (!commandLine->HasSwitch("type")) {
        app = new BrowserProcessHandler();
    }
    else if (commandLine->GetSwitchValue("type").ToString() == "renderer") {
        //--renderer-startup-dialog
        app = new RenderProcessHandler();
    }
    else {
        app = new OtherProcessHandler();
    }
    //启动子进程
    int exit_code = CefExecuteProcess(mainArgs, app, nullptr);
    if (exit_code >= 0) {
        return exit_code;
    }
    //CEF消息循环
    CefSettings settings;
    CefInitialize(mainArgs, settings, app.get(), nullptr);
    CefRunMessageLoop();
    CefShutdown();
    return 0;
}