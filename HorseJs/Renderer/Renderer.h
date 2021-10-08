#pragma once
#include "include/cef_app.h"
#include "V8Handler.h"
#include "MsgHandler/DialogR.h"
class Renderer :
    public CefApp,
    public CefRenderProcessHandler
{
public:
    Renderer();
    CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE { return this; }
    void OnWebKitInitialized() OVERRIDE;
    void OnBrowserDestroyed(CefRefPtr<CefBrowser> browser) OVERRIDE;
    void OnFocusedNodeChanged(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefDOMNode> node) OVERRIDE;
    bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) OVERRIDE;
    void OnContextCreated(CefRefPtr<CefBrowser> browser,CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) OVERRIDE;
private:
    IMPLEMENT_REFCOUNTING(Renderer);
    DISALLOW_COPY_AND_ASSIGN(Renderer);
    CefRefPtr<CefV8Handler> v8Handler;
};
