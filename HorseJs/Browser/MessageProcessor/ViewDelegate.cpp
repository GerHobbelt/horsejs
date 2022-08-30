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

// ��ǰҳ�浯���´���ʱ�˷�����ִ��
bool ViewDelegate::OnPopupBrowserViewCreated(CefRefPtr<CefBrowserView> browserView, CefRefPtr<CefBrowserView> popupBrowserView, bool isDevtools)
{
    //todo isDevtoolsû����
    //todo window.open���Ĳ��������
    CefWindow::CreateTopLevelWindow(new WindowPopupDelegate(popupBrowserView));
    return true;
}