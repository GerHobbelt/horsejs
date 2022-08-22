#pragma once
#include "include/cef_app.h"
#include <list>
class PageHandler :public CefClient, public CefLifeSpanHandler, public CefJSDialogHandler
{
public:
    PageHandler() = default;
    //获取LifeSpanHandler对象
    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
    //页面创建成功
    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
    //页面即将关闭
    void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

    CefRefPtr<CefJSDialogHandler> GetJSDialogHandler() override { return this; }
    bool OnBeforeUnloadDialog(CefRefPtr<CefBrowser> browser, const CefString& message_text, bool is_reload, CefRefPtr<CefJSDialogCallback> callback) override;
    bool OnJSDialog(CefRefPtr<CefBrowser> browser, const CefString& origin_url, JSDialogType dialog_type, const CefString& message_text, const CefString& default_prompt_text, CefRefPtr<CefJSDialogCallback> callback, bool& suppress_message) override;
private:
    IMPLEMENT_REFCOUNTING(PageHandler);
    std::list<CefRefPtr<CefBrowser>> browsers;
};
