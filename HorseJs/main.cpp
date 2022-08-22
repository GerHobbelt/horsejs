#include <windows.h>
#include <boost/process.hpp>
#include <iostream>
#include "App.h"
#include "json/json.hpp"
#include "Config.h"
namespace bp = boost::process;



/// <summary>
/// ����Node����
/// Ҫ����Node���̴����������ݣ�webserver�Ķ˿ںţ�
/// ��������������ģ����Կ��˸����߳������������
/// </summary>
void startNodeProcess() {
    bp::ipstream std_stream;
    auto dir = bp::start_dir("D:\\project\\horsejs\\HorseJs\\backend\\debug");
    bp::group g;
    bp::child c("D:\\sdk\\node\\Debug\\node.exe", "index.js", dir, g, bp::std_out > std_stream);
    std::string line;
    while (std_stream && std::getline(std_stream, line) && !line.empty()) {
        // ֻ����ôһ������ʱͨ��������ʽ���صģ�������ݷ���֮����ζ��Node��HTTP�����WebSocket�����Ѿ��ɹ�������
        nlohmann::json msg = nlohmann::json::parse(line);
        auto msgName = msg["name"].get<std::string>();
        if (msgName == "backendPort") {
            // �����߿���ָ���˿ڣ������������ָ���Ķ˿ڱ�ռ�ã���ô���ǻ������һ���˿�
            Config::get()["backendPort"] = msg["name"];
            break;
        }
    }
    //Ӧ����������������Node����
}

//����Ӧ�õ���ں���
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    CefEnableHighDPISupport();
    CefMainArgs main_args(hInstance);
    CefSettings settings;
    int exit_code = CefExecuteProcess(main_args, nullptr, nullptr);
    if (exit_code >= 0) {
        return exit_code;
    }
    std::thread nodeThread = std::thread(startNodeProcess);
    nodeThread.join();
    CefRefPtr<App> app(new App());
    CefInitialize(main_args, settings, app.get(), nullptr);
    CefRunMessageLoop();
    CefShutdown();
    return 0;
}