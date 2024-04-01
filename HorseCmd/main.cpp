// HorseCmd.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "json.hpp"
#include <fstream>
#include <filesystem>
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
using nlohmann::json;
static json config;
void initConfig()
{
    std::string buffer;
    std::ifstream f("build.json");
    f.seekg(0, std::ios::end);
    buffer.resize(f.tellg());
    f.seekg(0);
    f.read(buffer.data(), buffer.size());
    config = json::parse(buffer);
}


void start() {
    auto sdkPath = std::filesystem::path(config["sdkPath"].get<std::string>()).append("HorseJs.exe"); //路径不能有中文
    auto appPath = std::filesystem::path(config["appPath"].get<std::string>()); //路径不能有中文
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    // Start the child process. 
    if (!CreateProcess(sdkPath.wstring().data(), appPath.wstring().data(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return;
    }
    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);
    // Close process and thread handles. 
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}


void _tmain(int argc, TCHAR* argv[])
{
    bool flag = std::filesystem::exists("build.json");
    if (!flag) {
        std::cout << "didn't find build.json!\n";
        return;
    }
    initConfig();
//if (argc != 2)
//{
//    printf("Usage: %s [cmdline]\n", argv[0]);
//    return;
//}
    std::wstring arg = argv[1];
    if (arg == L"start") {
        start();
    }    
    //start
    //读取./build.json ,找到sdkPath和appPath，启动sdkPath下的HorseJs.exe，并把appPath传给HorseJs.exe
    
    //build
    //把appPath下的所有文件都以资源的形式打包到HorseJs.exe文件中，最后给HorseJs.exe改名
    //相应的还会处理icon和签名的事
    std::cout << "Hello World!\n";
    return;
}
