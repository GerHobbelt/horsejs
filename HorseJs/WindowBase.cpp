#include <windowsx.h>
#include <dwmapi.h>
#include "WindowBase.h"

namespace {
    static LRESULT CALLBACK RouteWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        if (msg == WM_NCCREATE)
        {
            //��Ȼ������Ϣ������ʵ��ָ�뱻�����ڴ��ڵ�extra data����
            //��RouteWindowMessage�״α�����ʱ��������ͨ��GetWindowLongPtrW�õ����ָ�룬
            //���Ա���Ҫ������һ��
            CREATESTRUCT* pCS = reinterpret_cast<CREATESTRUCT*>(lParam);
            LPVOID pThis = pCS->lpCreateParams;
            SetWindowLongPtr(hWnd, 0, reinterpret_cast<LONG_PTR>(pThis));
        }
        WindowBase* pWnd = reinterpret_cast<WindowBase*>(GetWindowLongPtrW(hWnd, 0));
        return pWnd->WindowProc(hWnd, msg, wParam, lParam);
    }
}

WindowBase::WindowBase() {
    CreateWindowFrameless();
}

void WindowBase::CreateWindowFrameless() {
    WNDCLASSEXW wcx{};
    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW | CS_VREDRAW;
    wcx.hInstance = nullptr;
    wcx.lpfnWndProc = &RouteWindowMessage;
    wcx.lpszClassName = L"BorderlessWindowClass";
    wcx.hbrBackground = CreateSolidBrush(RGB(226, 160, 160));
    wcx.hCursor = ::LoadCursorW(nullptr, IDC_ARROW);
    wcx.cbWndExtra = sizeof(WindowBase*);
    ::RegisterClassEx(&wcx);
    auto borderlessStyle = WS_POPUP | WS_THICKFRAME | WS_CAPTION | WS_SYSMENU | WS_VISIBLE;
    hWnd = CreateWindowEx(0, wcx.lpszClassName, L"���ڱ���", borderlessStyle, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr, nullptr, nullptr, static_cast<LPVOID>(this));
    ::SetWindowLongPtr(hWnd, GWL_STYLE, borderlessStyle);
    static const MARGINS shadow_state{ 1,1,1,1 };
    ::DwmExtendFrameIntoClientArea(hWnd, &shadow_state);
    ::SetWindowPos(hWnd, nullptr, 110, 110, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE);
}

LRESULT CALLBACK WindowBase::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {    
    switch (msg) {
        case WM_NCCALCSIZE: {
            return 0;
        }
        case WM_NCHITTEST: {
            return HitTest(hWnd, POINT{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) });
        }
        case WM_CLOSE: {
            ::DestroyWindow(hWnd);
            return 0;
        }
        case WM_DESTROY: {
            //todo ���д�������֮��Ҫ��Ҫ�˳�Ӧ��
            PostQuitMessage(0);
            return 0;
        }
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
LRESULT WindowBase::HitTest(HWND hwnd, POINT cursor) {
    const POINT border{
        ::GetSystemMetrics(SM_CXFRAME) + ::GetSystemMetrics(SM_CXPADDEDBORDER),
        ::GetSystemMetrics(SM_CYFRAME) + ::GetSystemMetrics(SM_CXPADDEDBORDER)
    };
    RECT winRect;
    if (!::GetWindowRect(hwnd, &winRect)) return HTNOWHERE;
    enum region_mask {
        client = 0b0000,
        left = 0b0001,
        right = 0b0010,
        top = 0b0100,
        bottom = 0b1000,
    };
    const auto result = left * (cursor.x < (winRect.left + border.x)) |
        right * (cursor.x >= (winRect.right - border.x)) |
        top * (cursor.y < (winRect.top + border.y)) |
        bottom * (cursor.y >= (winRect.bottom - border.y));
    switch (result) {
        case left: return HTLEFT;
        case right: return HTRIGHT;
        case top: return HTTOP;
        case bottom: return HTBOTTOM;
        case top | left: return HTTOPLEFT;
        case top | right: return HTTOPRIGHT;
        case bottom | left: return HTBOTTOMLEFT;
        case bottom | right: return HTBOTTOMRIGHT;
        case client: return HTCAPTION;
        default: return HTNOWHERE;
    }
}
