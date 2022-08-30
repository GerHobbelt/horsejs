#include <windows.h>
#include "include/cef_app.h"
#include "include/base/cef_scoped_ptr.h"
#include "include/cef_command_line.h"
#include "Main/Browser.h"
#include "Main/Other.h"
#include "Main/Renderer.h"
#include "Scheme/SchemeHandlerFactory.h"
#include "Common/json.hpp"


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
    CefSettings settings;
    if (command_line->HasSwitch("enable-chrome-runtime"))
    {
        settings.chrome_runtime = true;
    }
    CefInitialize(main_args, settings, app.get(), nullptr);
    CefRegisterSchemeHandlerFactory("horse", "app", new SchemeHandlerFactory());
    CefRunMessageLoop();
    CefShutdown();
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