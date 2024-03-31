#include <windows.h>
#include "WindowNative.h"


//整个应用的入口函数
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
    WindowNative win;
    MSG msg;
    while (::GetMessageW(&msg, nullptr, 0, 0) == TRUE) {
        ::TranslateMessage(&msg);
        ::DispatchMessageW(&msg);
    }
    return 0;
}