#pragma once
#include "include/cef_app.h"
#include <list>
class PageHandler :public CefClient, public CefLifeSpanHandler, public CefJSDialogHandler, public CefContextMenuHandler, public CefDragHandler
{
public:
    static CefRefPtr<PageHandler> getInstance();
    //��ȡLifeSpanHandler����
    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
    //ҳ�洴���ɹ�
    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
    //ҳ�漴���ر�
    void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

    CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() override { return this; }
    virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model) override;
    virtual bool OnContextMenuCommand(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, int command_id, EventFlags event_flags) override;

    CefRefPtr<CefDragHandler> GetDragHandler() override { return this; }
    virtual void OnDraggableRegionsChanged(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const std::vector<CefDraggableRegion>& regions) override;

    CefRefPtr<CefJSDialogHandler> GetJSDialogHandler() override { return this; }
    bool OnBeforeUnloadDialog(CefRefPtr<CefBrowser> browser, const CefString& message_text, bool is_reload, CefRefPtr<CefJSDialogCallback> callback) override;
    bool OnJSDialog(CefRefPtr<CefBrowser> browser, const CefString& origin_url, JSDialogType dialog_type, const CefString& message_text, const CefString& default_prompt_text, CefRefPtr<CefJSDialogCallback> callback, bool& suppress_message) override;
private:
    PageHandler() = default;
    IMPLEMENT_REFCOUNTING(PageHandler);
    std::list<CefRefPtr<CefBrowser>> browsers;
};
