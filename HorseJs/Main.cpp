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
//#include "main_message_loop.h"
//#include "main_message_loop_multithreaded_win.h"


// --renderer-startup-dialog 
IMPLEMENT_APP_NO_MAIN(TheWxApp);
IMPLEMENT_WX_THEME_SUPPORT;
int APIENTRY wWinMain(HINSTANCE hInstance, [[maybe_unused]] HINSTANCE hPrevInstance, [[maybe_unused]] LPTSTR lpCmdLine, int nCmdShow)
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
    //std::unique_ptr<MainMessageLoop> message_loop;
    //message_loop.reset(new MainMessageLoopMultithreadedWin);
    
    wxCmdLineArgType cmdLine = (char*)lpCmdLine;
    wxEntryStart(hInstance, hPrevInstance, cmdLine, nCmdShow);
    wxTheApp->CallOnInit();
    //TopWindow* win = new TopWindow();
    //win->Show();
    CefSettings settings;
    settings.multi_threaded_message_loop = true;
    CefInitialize(main_args, settings, app.get(), nullptr);
    CefRegisterSchemeHandlerFactory("http", "horse", new SchemeHandlerFactory());
    //int result = message_loop->Run();
    //CefRunMessageLoop();
    //CefDoMessageLoopWork();
    wxTheApp->OnRun();
    wxEntryCleanup();
    try
    {
        CefShutdown();
    }
    catch (...)
    {

    }
    
    return 0;
}



/*
* 
* �����ļ�
*       ָ����̬�ļ�Ŀ¼����ָ����������ҳ���ļ�·��
*       �Ƿ�������ʾ����
* npm��
*       ����exe����ص�dll�ļ�
*       
�򿪵����������ҵ��������Ե���ҳ�����ķ���
�ޱ��������ޱ߿�Ĵ���
MAC��ʹ��CEF�İ취
����ͼ�ꡢ�ļ�ϵͳ�����а��API
��μ����û�Դ��


2.  �� XXX Ŀ¼�´���һ�� horse.config.json ���ļ����������������ݣ�

```json
{
  "appDir": "./app/"
}
```

�����ļ��еľ��庬������

> appDir����ľ�̬�ļ���Ŀ¼������Ϊ���·����Ҳ����˵��� HTML/CSS/JS ���ļ���������� yourAppName ��Ŀ¼�ڣ�����Ŀ¼�±������һ�� index.html ���ļ���HorseJs ���صĵ�һ��ҳ���������

*/


 
