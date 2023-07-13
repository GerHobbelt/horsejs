#include <windowsx.h>
#include <dwmapi.h>
#include "Window.h"
#include "PageEnvironment.h"
using namespace Microsoft::WRL;


static wil::com_ptr<ICoreWebView2Controller> webviewController;
static wil::com_ptr<ICoreWebView2> webview;

LRESULT CALLBACK Window::RouteWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_NCCREATE)
    {
        //虽然窗口消息处理类实例指针被保存在窗口的extra data区域，
        //但RouteWindowMessage首次被调用时，还不能通过GetWindowLongPtrW得到这个指针，
        //所以必须要再设置一次
        CREATESTRUCT* pCS = reinterpret_cast<CREATESTRUCT*>(lParam);
        LPVOID pThis = pCS->lpCreateParams;
        SetWindowLongPtr(hWnd, 0, reinterpret_cast<LONG_PTR>(pThis));
    }
    Window* pWnd = reinterpret_cast<Window*>(GetWindowLongPtrW(hWnd, 0));
    return pWnd->WindowProc(hWnd, msg, wParam, lParam);
}

Window::Window(const HINSTANCE& hInstance) {
    //CreateWindowFrameless(hInstance);
    CreateWindowWithFrame(hInstance);
}

void Window::CreateWindowWithFrame(const HINSTANCE& hInstance)
{
    WNDCLASSEX wcx{};
    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW | CS_VREDRAW;
    wcx.lpfnWndProc = &Window::RouteWindowMessage;
    wcx.cbWndExtra = sizeof(Window*);
    wcx.hInstance = hInstance;
    wcx.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcx.hCursor = LoadCursor(hInstance, IDC_ARROW);
    wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcx.lpszClassName = L"BorderWindowClass";
    if (!RegisterClassEx(&wcx))
    {
        MessageBox(NULL, L"RegisterClassEx failed!", L"系统提示", NULL);
        return;
    }
    hwnd = CreateWindowEx(0, wcx.lpszClassName, L"窗口标题",WS_OVERLAPPEDWINDOW,
        110, 110,800, 600,NULL,NULL,hInstance, static_cast<LPVOID>(this));
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
}

void Window::CreateWindowFrameless(const HINSTANCE& hInstance) {
    WNDCLASSEX wcx{};
    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW | CS_VREDRAW;
    wcx.lpfnWndProc = &Window::RouteWindowMessage;
    wcx.cbWndExtra = sizeof(Window*);
    wcx.hInstance = hInstance;
    wcx.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcx.hCursor = LoadCursor(hInstance, IDC_ARROW);
    wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcx.lpszClassName = L"BorderlessWindowClass";
    RegisterClassEx(&wcx);
    auto borderlessStyle = WS_POPUP | WS_THICKFRAME | WS_CAPTION | WS_SYSMENU | WS_VISIBLE;
    hwnd = CreateWindowEx(0, wcx.lpszClassName, L"窗口标题", borderlessStyle, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr, nullptr, hInstance, static_cast<LPVOID>(this));
    SetWindowLongPtr(hwnd, GWL_STYLE, borderlessStyle);
    static const MARGINS shadow_state{ 1,1,1,1 };
    DwmExtendFrameIntoClientArea(hwnd, &shadow_state);
    SetWindowPos(hwnd, nullptr, 110, 110, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE);
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
}
void Window::CreatePageController()
{
    auto callBackInstance = Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(this, &Window::pageCtrlCallBack);
    auto env = PageEnvironment::Get()->Environment;
    auto result = env->CreateCoreWebView2Controller(hwnd, callBackInstance.Get());   
}


HRESULT Window::pageCtrlCallBack(HRESULT result, ICoreWebView2Controller* controller)
{
    //if (controller != nullptr) {
    //    webviewController = controller;
    //    webviewController->get_CoreWebView2(&webview);
    //}
    //wil::com_ptr<ICoreWebView2Settings> settings;
    //webview->get_Settings(&settings);
    //settings->put_IsScriptEnabled(TRUE);
    //settings->put_AreDefaultScriptDialogsEnabled(TRUE);
    //settings->put_IsWebMessageEnabled(TRUE);
    //RECT bounds;
    //GetClientRect(this->hwnd, &bounds);
    //webviewController->put_Bounds(bounds);
    //webview->Navigate(L"https://www.bing.com/");
    //return S_OK;

    auto ctrl = new PageController(controller);
    controllers.push_back(ctrl);
    RECT bounds;
    GetClientRect(hwnd, &bounds); //todo 多个ctrl
    auto a = controller->put_Bounds(bounds);
    flag = true;
    return S_OK;
}


LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {    
    switch (msg) {
        //case WM_NCCALCSIZE: {
        //    return 0;
        //}
        //case WM_NCHITTEST: {
        //    return HitTest(hWnd, POINT{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) });
        //}
        case WM_SIZE:{
            if (flag) {
                for (size_t i = 0; i < controllers.size(); i++)
                {
                    RECT bounds;
                    GetClientRect(hWnd, &bounds);
                    controllers[i]->Controller->put_Bounds(bounds);
                }
            }
        }
        break;
        case WM_CLOSE: {
            ::DestroyWindow(hWnd);
            return 0;
        }
        case WM_DESTROY: {
            //todo 所有窗口销毁之后要不要退出应用
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
