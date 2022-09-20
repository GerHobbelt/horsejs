#include "PageHandler.h"
#include "include/wrapper/cef_helpers.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "../MessageRouter/WindowRouter.h"
#include "../MessageRouter/AppRouter.h"
#include "../MessageRouter/ViewRouter.h"
#include "ViewDelegate.h"
#include "../../json/json.hpp"

namespace {
    CefRefPtr<PageHandler> instance = nullptr;
}

CefRefPtr<PageHandler> PageHandler::getInstance() {
    if (!instance) {
        instance = new PageHandler();
    }
    return instance;
}
void PageHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
    browsers.push_back(browser);
}
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
        instance = nullptr;
        CefQuitMessageLoop();
    }
}
void PageHandler::OnDraggableRegionsChanged(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const std::vector<CefDraggableRegion>& regions)
{
    CefRefPtr<CefBrowserView> browser_view = CefBrowserView::GetForBrowser(browser);
    if (browser_view)
    {
        CefRefPtr<CefWindow> window = browser_view->GetWindow();
        if (window) window->SetDraggableRegions(regions);
    }
}

bool PageHandler::OnBeforeUnloadDialog(CefRefPtr<CefBrowser> browser, const CefString& message_text, bool is_reload, CefRefPtr<CefJSDialogCallback> callback) {
    HWND hwnd = browser->GetHost()->GetWindowHandle();
    int msgboxID = MessageBox(hwnd, L"您编辑的内容尚未保存.\n确定要关闭窗口吗?", L"系统提示", MB_ICONEXCLAMATION | MB_OKCANCEL);
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
        MessageBox(hwnd, message_text.c_str(), L"系统提示", MB_ICONEXCLAMATION | MB_OK);
        callback->Continue(true, CefString());
    }
    else if (dialog_type == JSDialogType::JSDIALOGTYPE_CONFIRM) {
        int msgboxID = MessageBox(hwnd, message_text.c_str(), L"系统提示", MB_ICONEXCLAMATION | MB_YESNO);
        callback->Continue(msgboxID == IDYES, CefString());
    }
    else if (dialog_type == JSDialogType::JSDIALOGTYPE_PROMPT) {
        //todo
    }
    return true;
}

void PageHandler::OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model)
{
    model->Clear();
    model->AddItem(MENU_ID_USER_FIRST, L"打开开发者调试工具");
    CefRefPtr<CefMenuModel> subModel = model->AddSubMenu(MENU_ID_USER_FIRST + 1, L"这是一个包含子菜单的测试菜单");
    subModel->AddItem(MENU_ID_USER_FIRST + 2, L"这是子菜单1");
    subModel->AddItem(MENU_ID_USER_FIRST + 3, L"这是子菜单2");
    model->AddSeparator();
    model->AddCheckItem(MENU_ID_USER_FIRST + 4, L"这是一个包含复选框的菜单");
    model->SetChecked(MENU_ID_USER_FIRST + 4, true);
    model->AddRadioItem(MENU_ID_USER_FIRST + 5, L"这是一个包含复选框的菜单", 888);
    model->AddRadioItem(MENU_ID_USER_FIRST + 6, L"这是一个包含单选框的菜单", 888);
    model->SetChecked(MENU_ID_USER_FIRST + 6, true);
}

bool PageHandler::OnContextMenuCommand(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, int command_id, EventFlags event_flags)
{
    switch (command_id)
    {
    case MENU_ID_USER_FIRST: {
        CefBrowserSettings browserSettings;
        CefWindowInfo windowInfo;
        CefPoint mousePoint(params->GetXCoord(), params->GetYCoord());
        browser->GetHost()->ShowDevTools(windowInfo, this, browserSettings, mousePoint);
        break;
    }
    default: {
        std::wstring msg = L"你点击的标签ID：" + std::to_wstring(command_id);
        MessageBox(NULL, (LPWSTR)msg.c_str(), L"系统提示", MB_ICONEXCLAMATION | MB_OKCANCEL);
        break;
    }
    }
    return true;
}

bool PageHandler::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
{
    CEF_REQUIRE_UI_THREAD();
    std::string messageName = message->GetName();
    std::string msgStr = message->GetArgumentList()->GetString(0).ToString();
    nlohmann::json messageParam = nlohmann::json::parse(msgStr);
    nlohmann::json result = {};
    if (messageName == "Win") {
        CefRefPtr<CefBrowserView> browserView = CefBrowserView::GetForBrowser(browser);        
        auto delegate = browserView->GetWindow()->GetDelegate().get();
        CefRefPtr<WindowDelegate> windowDelegate = static_cast<WindowDelegate*>(delegate);
        auto windowRouter = WindowRouter::getInstance();  
        windowRouter->routeMessage(messageParam, windowDelegate, result);
    }
    else if (messageName == "View") {
        CefRefPtr<CefBrowserView> browserView = CefBrowserView::GetForBrowser(browser);
        auto viewRouter = ViewRouter::getInstance();
        viewRouter->routeMessage(messageParam, browserView, result);
    }
    else if (messageName == "App") {
        auto appRouter = AppRouter::getInstance();
        appRouter->routeMessage(messageParam, result);
    }
    result["__msgId"] = messageParam["__msgId"].get<int64>();
    std::string resultStr = result.dump();
    CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(resultStr);
    frame->SendProcessMessage(PID_RENDERER, msg);
    return true;
}
