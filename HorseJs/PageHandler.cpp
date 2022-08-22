#include "PageHandler.h"
#include "include/wrapper/cef_helpers.h"
//ҳ�洴���ɹ�
void PageHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
    browsers.push_back(browser);
}
//ҳ�漴���ر�
void PageHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
    std::list<CefRefPtr<CefBrowser>>::iterator bit = browsers.begin();
    for (; bit != browsers.end(); ++bit) {
        if ((*bit)->IsSame(browser)) {
            browsers.erase(bit);
            break;
        }
    }
    if (browsers.empty()) {
        CefQuitMessageLoop();
    }
}
bool PageHandler::OnBeforeUnloadDialog(CefRefPtr<CefBrowser> browser, const CefString& message_text, bool is_reload, CefRefPtr<CefJSDialogCallback> callback) {
    HWND hwnd = browser->GetHost()->GetWindowHandle();
    int msgboxID = MessageBox(hwnd, L"���༭��������δ����.\nȷ��Ҫ�رմ�����?", L"ϵͳ��ʾ", MB_ICONEXCLAMATION | MB_OKCANCEL);
    if (msgboxID == IDOK) {
        callback->Continue(true, CefString());
    }
    else {
        callback->Continue(false, CefString());
    }
    return true;
}
bool PageHandler::OnJSDialog(CefRefPtr<CefBrowser> browser,
    const CefString& origin_url,
    JSDialogType dialog_type,
    const CefString& message_text,
    const CefString& default_prompt_text,
    CefRefPtr<CefJSDialogCallback> callback,
    bool& suppress_message) {
    suppress_message = false;
    HWND hwnd = browser->GetHost()->GetWindowHandle();
    if (dialog_type == JSDialogType::JSDIALOGTYPE_ALERT) {
        MessageBox(hwnd, message_text.c_str(), L"ϵͳ��ʾ", MB_ICONEXCLAMATION | MB_OK);
        callback->Continue(true, CefString());
    }
    else if (dialog_type == JSDialogType::JSDIALOGTYPE_CONFIRM) {
        int msgboxID = MessageBox(hwnd, message_text.c_str(), L"ϵͳ��ʾ", MB_ICONEXCLAMATION | MB_YESNO);
        callback->Continue(msgboxID == IDYES, CefString());
    }
    else if (dialog_type == JSDialogType::JSDIALOGTYPE_PROMPT) {
        //�ⲿ���߼��Ժ󽲽�
    }
    return true;
}
