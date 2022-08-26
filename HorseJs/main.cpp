#include <windows.h>
#include "App.h"
#include "json/json.hpp"
#include "Config.h"
#include "Renderer.h"
#include "Other.h"
#include "WebSocketClient.h"

//����Ӧ�õ���ں���
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    CefEnableHighDPISupport();
    //�ռ������в���
    CefMainArgs main_args(hInstance);
    CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
    command_line->InitFromString(::GetCommandLineW());
    //Ϊ��ͬ���̴�����ͬ�Ĵ������
    CefRefPtr<CefApp> app;
    WebSocketClient wsClient;
    if (!command_line->HasSwitch("type")) {
        Config::init();
        if (command_line->HasSwitch("horse-port")) {
            config["httpAndWebSocketServicePort"] = command_line->GetSwitchValue("horse-port").ToString();
        }        
        //����websocket�ͻ���
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
    //�����ӽ���
    int exit_code = CefExecuteProcess(main_args, app, nullptr);
    if (exit_code >= 0) {
        return exit_code;
    }
    //CEF��Ϣѭ��
    CefSettings settings;
    CefInitialize(main_args, settings, app.get(), nullptr);
    CefRunMessageLoop();
    wsClient.terminate();
    CefShutdown();
    return 0;
}