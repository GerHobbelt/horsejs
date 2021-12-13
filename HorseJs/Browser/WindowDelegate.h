#pragma once
#include <fstream>
#include <filesystem>
#include "include/views/cef_window_delegate.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "../Common/Config.h"
#include "../Common/json.hpp"
#include <wx/nativewin.h>
#include <wx/menu.h>
#include "NativeWindow.h"
using nlohmann::json;
class WindowDelegate : public CefWindowDelegate
{
public:
    explicit WindowDelegate(CefRefPtr<CefBrowserView> browser_view,bool isFrameless = false, bool isDevWindow = false) : 
        browser_view_(browser_view), 
        isFrameless(isFrameless) ,
        isDevWindow(isDevWindow)
    {}

    void OnWindowCreated(CefRefPtr<CefWindow> window) override;
    bool IsFrameless(CefRefPtr<CefWindow> window) override
    {
        return isFrameless;
    };
    void OnWindowDestroyed(CefRefPtr<CefWindow> window) override
    {
        browser_view_ = nullptr;
    };
    bool CanClose(CefRefPtr<CefWindow> window) override;
    CefSize GetPreferredSize(CefRefPtr<CefView> view);
    CefSize GetMinimumSize(CefRefPtr<CefView> view) override;
    CefSize GetMaximumSize(CefRefPtr<CefView> view) override;
    CefRefPtr<CefBrowserView> browser_view_;
    NativeWindow* nativeWindow;
private:
    void PrepareIcon(CefRefPtr<CefImage> image, double scale_factor, const std::string& name);
    CefSize getSizeConfig(std::string_view configName);
    bool isFrameless;
    bool isDevWindow;
    IMPLEMENT_REFCOUNTING(WindowDelegate);
    DISALLOW_COPY_AND_ASSIGN(WindowDelegate);

};

