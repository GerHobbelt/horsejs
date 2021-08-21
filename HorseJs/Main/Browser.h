#pragma once
#include "include/cef_app.h"
class Browser :
    public CefApp, 
    public CefBrowserProcessHandler {
public:
    Browser() = default;
    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE { return this; }
    virtual void OnContextInitialized() OVERRIDE;
    CefRefPtr<CefClient> GetDefaultClient() OVERRIDE;
private:
    IMPLEMENT_REFCOUNTING(Browser);
};
