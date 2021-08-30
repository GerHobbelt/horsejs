#include <windows.h>
#include "include/cef_app.h"
#include "include/base/cef_scoped_ptr.h"
#include "include/cef_command_line.h"
#include "include/cef_sandbox_win.h"
#include "Main/Browser.h"
#include "Main/Other.h"
#include "Main/Renderer.h"
#include "Scheme/SchemeHandlerFactory.h"

#if defined(CEF_USE_SANDBOX)
// The cef_sandbox.lib static library may not link successfully with all VS versions.
#pragma comment(lib, "cef_sandbox.lib")
#endif

int APIENTRY wWinMain(HINSTANCE hInstance, [[maybe_unused]] HINSTANCE hPrevInstance, [[maybe_unused]] LPTSTR lpCmdLine, int nCmdShow)
{
    CefEnableHighDPISupport();
    void* sandbox_info = nullptr;
#if defined(CEF_USE_SANDBOX)
    CefScopedSandboxInfo scoped_sandbox;
    sandbox_info = scoped_sandbox.sandbox_info();
#endif
    CefMainArgs main_args(hInstance);
    CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
    command_line->InitFromString(::GetCommandLineW());
    CefRefPtr<CefApp> app;
    if (!command_line->HasSwitch("type"))
    {
        app = new Browser();
    }
    else if (command_line->GetSwitchValue("type").ToString() == "renderer")
    {
        app = new Renderer();
    }
    else
    {
        app = new Other();
    }
    int exit_code = CefExecuteProcess(main_args, app, sandbox_info);
    if (exit_code >= 0) return exit_code;
    CefSettings settings;
    if (command_line->HasSwitch("enable-chrome-runtime"))
    {
        settings.chrome_runtime = true;
    }
#if !defined(CEF_USE_SANDBOX)
    settings.no_sandbox = true;
#endif
    // Initialize CEF.
    CefInitialize(main_args, settings, app.get(), sandbox_info);
    CefRegisterSchemeHandlerFactory("horse", "tests", new SchemeHandlerFactory());
    // Run the CEF message loop. This will block until CefQuitMessageLoop() is called.
    CefRunMessageLoop();
    // Shut down CEF.
    CefShutdown();
    return 0;
}

/*
打开调试器或者找到其他可以调试页面代码的方法
无标题栏和无边框的窗口
MAC下使用CEF的办法
托盘图标、文件系统、剪切板等API
如何加密用户源码

*/