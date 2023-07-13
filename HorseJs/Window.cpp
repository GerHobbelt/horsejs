#include <windowsx.h>
#include <dwmapi.h>
#include "Window.h"
#include "PageEnvironment.h"


using namespace Microsoft::WRL;
LRESULT CALLBACK Window::RouteWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_NCCREATE)
    {
        //��Ȼ������Ϣ������ʵ��ָ�뱻�����ڴ��ڵ�extra data����
        //��RouteWindowMessage�״α�����ʱ��������ͨ��GetWindowLongPtrW�õ����ָ�룬
        //���Ա���Ҫ������һ��
        CREATESTRUCT* pCS = reinterpret_cast<CREATESTRUCT*>(lParam);
        LPVOID pThis = pCS->lpCreateParams;
        SetWindowLongPtr(hWnd, 0, reinterpret_cast<LONG_PTR>(pThis));
    }
    Window* pWnd = reinterpret_cast<Window*>(GetWindowLongPtrW(hWnd, 0));
    return pWnd->WindowProc(hWnd, msg, wParam, lParam);
}

Window::Window() {
    CreateWindowFrameless();
}

void Window::CreateWindowFrameless() {
    WNDCLASSEXW wcx{};
    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW | CS_VREDRAW;
    wcx.hInstance = nullptr;
    wcx.lpfnWndProc = &Window::RouteWindowMessage;
    wcx.lpszClassName = L"BorderlessWindowClass";
    wcx.hbrBackground = NULL;
    wcx.hCursor = ::LoadCursorW(nullptr, IDC_ARROW);
    wcx.cbWndExtra = sizeof(Window*);
    ::RegisterClassEx(&wcx);
    auto borderlessStyle = WS_POPUP | WS_THICKFRAME | WS_CAPTION | WS_SYSMENU | WS_VISIBLE;
    hwnd = CreateWindowEx(0, wcx.lpszClassName, L"���ڱ���", borderlessStyle, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr, nullptr, nullptr, static_cast<LPVOID>(this));
    ::SetWindowLongPtr(hwnd, GWL_STYLE, borderlessStyle);
    static const MARGINS shadow_state{ 1,1,1,1 };
    ::DwmExtendFrameIntoClientArea(hwnd, &shadow_state);
    ::SetWindowPos(hwnd, nullptr, 110, 110, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE);
}
void Window::CreatePageController()
{
    auto callBackInstance = Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(this, &Window::pageCtrlCallBack);
    PageEnvironment::Get()->Environment->CreateCoreWebView2Controller(hwnd, callBackInstance.Get());    
}


HRESULT Window::pageCtrlCallBack(HRESULT result, ICoreWebView2Controller* controller)
{
    auto ctrl = new PageController(controller);
    controllers.push_back(ctrl);
    RECT bounds;
    GetClientRect(hwnd, &bounds); //todo ���ctrl
    controller->put_Bounds(bounds);
    return S_OK;
}


LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {    
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
LRESULT Window::HitTest(HWND hwnd, POINT cursor) {
    const POINT border{
        GetSystemMetrics(SM_CXFRAME) + GetSystemMetrics(SM_CXPADDEDBORDER),
        GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CXPADDEDBORDER)
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
