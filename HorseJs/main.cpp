#include <windows.h>
#include <boost/process.hpp>
#include <iostream>
#include "App.h"
#include "json/json.hpp"
namespace bp = boost::process;


int backendPort = -1;

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
        // ��ð����������װ��һ������
        // �����߿������������ע��ص�����
        // �ص��������������������һ��map����
        // �յ���msg.name����map�����key
        // �����յ�һ��msg���Ϳ��Ե���������ע�����Ļص�������
        // ����msg��value������Ϊ�������ݸ��ص�����
        nlohmann::json msg = nlohmann::json::parse(line);
        auto msgName = msg["name"].get<std::string>();
        if (msgName == "backendPort") {
            backendPort = msg["value"].get<int>();
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
    std::thread th1;
    th1 = std::thread(startNodeProcess);
    while (backendPort == -1)
    {
        //wait
    }
    CefRefPtr<App> app(new App());
    CefInitialize(main_args, settings, app.get(), nullptr);
    CefRunMessageLoop();
    th1.detach();
    CefShutdown();
    return 0;
}