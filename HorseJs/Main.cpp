<<<<<<< HEAD
﻿#include <windows.h>
#include "json.hpp"
#include <shellapi.h>
#include <fstream>
#include <filesystem>
#include "App.h"
using nlohmann::json;
void readFile()
{
//std::wstring buffer;            // stores file contents
//FILE* f;
//_wfopen_s(&f, L"build.json", L"rtS, ccs=UTF-8");
//// Failed to open file
//if (f == NULL)
//{
//    // ...handle some error...
//}
//struct _stat fileinfo;
//_wstat(L"build.json", &fileinfo);
//size_t filesize = fileinfo.st_size;
//if (filesize > 0)
//{
//    buffer.resize(filesize);
//    size_t wchars_read = fread(&(buffer.front()), sizeof(wchar_t), filesize, f);
//    buffer.resize(wchars_read);
//    buffer.shrink_to_fit();
//}
//fclose(f);
}

bool checkRegKey(const HKEY& key, const std::wstring& subKey) {
    size_t bufferSize = 20; //每位4个，共4位，加3个点，再多给一位，后面会截掉多余的
    std::wstring valueBuf;
    valueBuf.resize(bufferSize);
    auto valueSize = static_cast<DWORD>(bufferSize * sizeof(wchar_t));
    auto rc = RegGetValue(key, subKey.c_str(), L"pv", RRF_RT_REG_SZ, nullptr,
        static_cast<void*>(valueBuf.data()), &valueSize
    );
    if (rc == ERROR_SUCCESS)
    {
        valueSize /= sizeof(wchar_t);
        valueBuf.resize(static_cast<size_t>(valueSize - 1));//todo 这个版本号可能有用
        if (valueBuf.empty() || valueBuf == L"0.0.0.0") {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}

bool checkRuntime()
{
    std::wstring regSubKey = L"\\Microsoft\\EdgeUpdate\\Clients\\{F3017226-FE2A-4295-8BDF-00C3A9A7E4C5}";
    bool hasRuntime = checkRegKey(HKEY_LOCAL_MACHINE, L"SOFTWARE\\WOW6432Node"+regSubKey);
    if (hasRuntime) return true;
    hasRuntime = checkRegKey(HKEY_CURRENT_USER, L"Software"+regSubKey);
    if (!hasRuntime) {
        auto result = MessageBox(nullptr, L"您得系统中缺少必要组件，现在为您打开下载链接，下载相关组件？", 
            L"系统提示", MB_OKCANCEL | MB_ICONINFORMATION | MB_DEFBUTTON1);
        if (result == IDOK) {
            ShellExecute(0, 0, L"https://go.microsoft.com/fwlink/p/?LinkId=2124703", 0, 0, SW_SHOW);
        }
        return false;
    }
    return true;
}

static json config;
void initConfig()
{
    std::string buffer;
    std::ifstream f("app/app.json");
    f.seekg(0, std::ios::end);
    buffer.resize(f.tellg());
    f.seekg(0);
    f.read(buffer.data(), buffer.size());
    config = json::parse(buffer);
}


//entry point
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    auto result = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (result != S_OK) {
        return 0;
    }
    auto flag = checkRuntime();
    if (!flag) return 0;
    initConfig();
    App::Init(hInstance);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }    
    App::Dispose();
    CoUninitialize();
    return (int)msg.wParam;
=======
#include <windows.h>
#include "WindowNative.h"


//����Ӧ�õ���ں���
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    WindowNative win;
    MSG msg;
    while (::GetMessageW(&msg, nullptr, 0, 0) == TRUE) {
        ::TranslateMessage(&msg);
        ::DispatchMessageW(&msg);
    }
    return 0;
>>>>>>> remotes/GerHobbelt/master
}