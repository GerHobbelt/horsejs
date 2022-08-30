#include "ViewDelegate.h"
#include "./Window/WindowPopupDelegate.h"

namespace {
    CefRefPtr<ViewDelegate> instance = nullptr;
}

ViewDelegate::~ViewDelegate() {
    instance = nullptr;
}

CefRefPtr<ViewDelegate> ViewDelegate::getInstance() {
    if (!instance) {
        instance = new ViewDelegate();
    }
    return instance;
}

// 当前页面弹出新窗口时此方法被执行
bool ViewDelegate::OnPopupBrowserViewCreated(CefRefPtr<CefBrowserView> browserView, CefRefPtr<CefBrowserView> popupBrowserView, bool isDevtools)
{
    //todo isDevtools没用上
    //todo window.open传的参数在哪里？
    CefWindow::CreateTopLevelWindow(new WindowPopupDelegate(popupBrowserView));
    return true;
}