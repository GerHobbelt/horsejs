#pragma once
#include "include/cef_client.h"
#include <list>
#include <set>
#include "include/wrapper/cef_message_router.h"
class Handler :
    public CefClient,
    public CefDisplayHandler,
    public CefLifeSpanHandler,
    public CefLoadHandler,
    public CefDragHandler
{
public:
    explicit Handler();
    ~Handler();
    static Handler* GetInstance();
    virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE { return this; }
    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE { return this; }
    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE { return this; }
    CefRefPtr<CefDragHandler> GetDragHandler() OVERRIDE { return this; }
    virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) OVERRIDE;
    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
    virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
    virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
    virtual bool OnDragEnter(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDragData> dragData, CefDragHandler::DragOperationsMask mask) OVERRIDE;
    virtual void OnDraggableRegionsChanged(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const std::vector<CefDraggableRegion>& regions) OVERRIDE;
    bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) OVERRIDE;
    virtual void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl) OVERRIDE;
    void CloseAllBrowsers(bool force_close);
    bool IsClosing() const { return is_closing_; }
    static bool IsChromeRuntimeEnabled();
    CefRefPtr<CefMessageRouterBrowserSide> message_router_;
    std::set<CefMessageRouterBrowserSide::Handler*> message_handler_set_;
private:
    const bool use_views_;
    typedef std::list<CefRefPtr<CefBrowser>> BrowserList;
    BrowserList browser_list_;
    bool is_closing_;
    IMPLEMENT_REFCOUNTING(Handler);
};

