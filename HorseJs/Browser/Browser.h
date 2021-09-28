#pragma once
#include "include/cef_app.h"
class Browser :
    public CefApp, 
    public CefBrowserProcessHandler {
public:
    Browser() = default;
    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override { return this; }
    virtual void OnContextInitialized() override;
    CefRefPtr<CefClient> GetDefaultClient() override;
private:
    IMPLEMENT_REFCOUNTING(Browser);
};
