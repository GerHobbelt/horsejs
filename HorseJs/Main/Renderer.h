#pragma once
#include "include/cef_app.h"
class Renderer :
    public CefApp,
    public CefRenderProcessHandler
{
public:
    Renderer() = default;
    CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE { return this; }
    void OnWebKitInitialized() OVERRIDE;
    void OnBrowserDestroyed(CefRefPtr<CefBrowser> browser) OVERRIDE;
    void OnFocusedNodeChanged(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefDOMNode> node) OVERRIDE;
private:
    IMPLEMENT_REFCOUNTING(Renderer);
    DISALLOW_COPY_AND_ASSIGN(Renderer);
};
