#pragma once
#include "include/cef_app.h"
#include "V8Handler.h"
class Renderer :
    public CefApp,
    public CefRenderProcessHandler
{
public:
    Renderer();
    ~Renderer();
    CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override { return this; }
    void OnWebKitInitialized() override;
    void OnBrowserDestroyed(CefRefPtr<CefBrowser> browser) override;
    void OnFocusedNodeChanged(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefDOMNode> node) override;
    bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) override;
    void OnContextCreated(CefRefPtr<CefBrowser> browser,CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) override;
private:
    IMPLEMENT_REFCOUNTING(Renderer);
    DISALLOW_COPY_AND_ASSIGN(Renderer);
    V8Handler* v8Handler;
};
class ReleaseCallback : public CefV8ArrayBufferReleaseCallback {
public:
    void ReleaseBuffer(void* buffer) override { std::free(buffer); }
    IMPLEMENT_REFCOUNTING(ReleaseCallback);
};
