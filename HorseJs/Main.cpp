#include <windows.h>
#include <wx/wx.h>
#include "include/cef_app.h"
#include "include/base/cef_scoped_refptr.h"
#include "include/cef_command_line.h"
#include "Browser/Browser.h"
#include "Other/Other.h"
#include "Renderer/Renderer.h"
#include "Scheme/SchemeHandlerFactory.h"
#include "Browser/TheWxApp.h"
#include "Browser/TopWindow.h"


// --renderer-startup-dialog 
// http://localhost:10086/json
// devtools://devtools/bundled/inspector.html?ws=localhost:10086/devtools/page/3DEDA81C103D19CDDB8BCC7B53BBC563
IMPLEMENT_APP_NO_MAIN(TheWxApp);
IMPLEMENT_WX_THEME_SUPPORT;
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    CefEnableHighDPISupport();
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
    int exit_code = CefExecuteProcess(main_args, app, nullptr);
    if (exit_code >= 0) return exit_code;
    
    wxCmdLineArgType cmdLine = (char*)lpCmdLine;
    wxEntryStart(hInstance, hPrevInstance, cmdLine, nCmdShow);
    wxTheApp->CallOnInit();
    //TopWindow* win = new TopWindow();
    //win->Show();
    CefSettings settings;
    settings.multi_threaded_message_loop = true;
#if defined(_DEBUG)
    settings.log_severity = cef_log_severity_t::LOGSEVERITY_INFO;
#else
    settings.log_severity = cef_log_severity_t::LOGSEVERITY_ERROR;
#endif
    
    CefInitialize(main_args, settings, app.get(), nullptr);
    CefRegisterSchemeHandlerFactory("http", "horse", new SchemeHandlerFactory());
    //int result = message_loop->Run();
    //CefRunMessageLoop();
    //CefDoMessageLoopWork();
    wxTheApp->OnRun();
    wxEntryCleanup();
    CefShutdown();    
    return 0;
}



/*
* 
* 配置文件
*       指定静态文件目录，或指定具体的入口页面文件路径
*       是否立即显示窗口
* npm包
*       下载exe和相关的dll文件
*       
打开调试器或者找到其他可以调试页面代码的方法
无标题栏和无边框的窗口
MAC下使用CEF的办法
托盘图标、文件系统、剪切板等API
如何加密用户源码


2.  在 XXX 目录下创建一个 horse.config.json 的文件，并输入如下内容：

```json
{
  "appDir": "./app/"
}
```

配置文件中的具体含义如下

> appDir：你的静态文件的目录，必须为相对路径，也就是说你的 HTML/CSS/JS 等文件必须放置在 yourAppName 子目录内，该子目录下必须包含一个 index.html 的文件，HorseJs 加载的第一个页面就是它；

*/


 
