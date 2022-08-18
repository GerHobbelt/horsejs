#pragma once
#include "include/cef_app.h"
class App : public CefApp, public CefBrowserProcessHandler
{
public:
    App() = default;
    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override { return this; }
    void OnContextInitialized() override;
private:
    IMPLEMENT_REFCOUNTING(App);
};

