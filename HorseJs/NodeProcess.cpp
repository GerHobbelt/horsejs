#include "NodeProcess.h"
#include "Config.h"
/// <summary>
/// ����Node����
/// �ҵ�һ�����õĶ˿ں�
/// ������˿ںŴ��ݸ�Node����
/// </summary>
void NodeProcess::run() {
    asio::io_service service;
    asio::ip::tcp::acceptor acceptor(service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 0));
    unsigned short port = acceptor.local_endpoint().port();
    //todo ��һ�����̵�ʱ���������һ����������ռ��������˿ڣ�������backendʹ������˿ڳ�������
    auto backendPath = getExeDir();
    auto nodePath = backendPath;
    auto cmd = nodePath.append("node\\horseNode.exe").wstring() + L" index.js " + std::to_wstring(port);
    auto workingDir = boost::process::start_dir(backendPath.append("backend").wstring());
    nodeProcess = new bp::child(cmd, workingDir);
    config["backendHttpService"] = "http://localhost:" + std::to_string(port);
    config["backendWebSocketService"] = "ws://localhost:" + std::to_string(port);
}
fs::path NodeProcess::getExeDir() {
    //todo mac
    WCHAR _exePath[MAX_PATH];
    DWORD result = GetModuleFileName(NULL, _exePath, MAX_PATH);
    if (result == 0) {
        throw "Error in getting module filename.";
    }
    std::wstring exePathStr(_exePath);
    auto exePath = fs::path(exePathStr);
    return exePath.remove_filename();
}
void NodeProcess::terminate() {
    nodeProcess->terminate();
}