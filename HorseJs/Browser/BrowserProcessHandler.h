#pragma once
#include "include/cef_app.h"
#include "WebSocketClient.h"
#include "../Config.h"
class BrowserProcessHandler : public CefApp, public CefBrowserProcessHandler
{
public:
    BrowserProcessHandler(std::string& port);
    ~BrowserProcessHandler();
    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override { return this; }
    void OnContextInitialized() override;
private:
    IMPLEMENT_REFCOUNTING(BrowserProcessHandler);
};
