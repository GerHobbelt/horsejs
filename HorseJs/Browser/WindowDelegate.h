#pragma once
#include "include/views/cef_window_delegate.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
class WindowDelegate :
    public CefWindowDelegate
{
public:
    explicit WindowDelegate(CefRefPtr<CefBrowserView> browser_view) : browser_view_(browser_view) {}
    void OnWindowCreated(CefRefPtr<CefWindow> window) OVERRIDE
    {
        // Add the browser view and show the window.
        window->AddChildView(browser_view_);
        window->Show();
        CefSize size{ 800,600 };
        window->CenterWindow(size);
        // Give keyboard focus to the browser view.
        browser_view_->RequestFocus();
    }
    bool IsFrameless(CefRefPtr<CefWindow> window) OVERRIDE
    {
        return true;
    }
    void OnWindowDestroyed(CefRefPtr<CefWindow> window) OVERRIDE
    {
        browser_view_ = nullptr;
    }
    bool CanClose(CefRefPtr<CefWindow> window) OVERRIDE
    {
        CefRefPtr<CefBrowser> browser = browser_view_->GetBrowser();
        if (browser)
            return browser->GetHost()->TryCloseBrowser();
        return true;
    }
    CefSize GetPreferredSize(CefRefPtr<CefView> view) OVERRIDE
    {
        return CefSize(800, 600);
    }
private:
    CefRefPtr<CefBrowserView> browser_view_;
    IMPLEMENT_REFCOUNTING(WindowDelegate);
    DISALLOW_COPY_AND_ASSIGN(WindowDelegate);
};

