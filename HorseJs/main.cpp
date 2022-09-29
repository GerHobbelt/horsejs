#include <windows.h>
#include "Browser/BrowserProcessHandler.h"
#include "Render/RenderProcessHandler.h"
#include "Other/OtherProcessHandler.h"

//����Ӧ�õ���ں���
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    CefEnableHighDPISupport();
    //�ռ������в���
    CefMainArgs mainArgs(hInstance);
    CefRefPtr<CefCommandLine> commandLine = CefCommandLine::CreateCommandLine();
    commandLine->InitFromString(::GetCommandLineW());//todo mac
    //Ϊ��ͬ���̴�����ͬ�Ĵ������
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
    //�����ӽ���
    int exit_code = CefExecuteProcess(mainArgs, app, nullptr);
    if (exit_code >= 0) {
        return exit_code;
    }
    //CEF��Ϣѭ��
    CefSettings settings;
    CefInitialize(mainArgs, settings, app.get(), nullptr);
    CefRunMessageLoop();
    CefShutdown();
    return 0;
}