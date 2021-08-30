#pragma once
#include "include/cef_client.h"
#include <list>
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
    // CefDisplayHandler methods:
    virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) OVERRIDE;
    // CefLifeSpanHandler methods:
    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
    virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
    virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
    virtual bool OnDragEnter(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDragData> dragData, CefDragHandler::DragOperationsMask mask) OVERRIDE;
    virtual void OnDraggableRegionsChanged(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const std::vector<CefDraggableRegion>& regions) OVERRIDE;
    // CefLoadHandler methods:
    virtual void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl) OVERRIDE;
    // Request that all existing browser windows close.
    void CloseAllBrowsers(bool force_close);
    bool IsClosing() const { return is_closing_; }
    // Returns true if the Chrome runtime is enabled.
    static bool IsChromeRuntimeEnabled();
private:
    void PlatformTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title);
    const bool use_views_;
    typedef std::list<CefRefPtr<CefBrowser>> BrowserList;
    BrowserList browser_list_;
    bool is_closing_;
    IMPLEMENT_REFCOUNTING(Handler);
};

