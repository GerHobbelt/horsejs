#pragma once
#include "include/views/cef_window.h"
#include "include/views/cef_browser_view.h"
#include "../../json/json.hpp"
#include <list>
class WindowDelegate : public CefWindowDelegate, public CefBrowserViewDelegate
{
public:
    explicit WindowDelegate(const nlohmann::json& config);
    void AddOverlayView(const nlohmann::json& overlayViewConfig);
    bool IsFrameless(CefRefPtr<CefWindow> window) override;
    void OnWindowCreated(CefRefPtr<CefWindow> window) override;
    void OnWindowDestroyed(CefRefPtr<CefWindow> window) override;
    CefRect GetInitialBounds(CefRefPtr<CefWindow> window) override;
    bool CanClose(CefRefPtr<CefWindow> window) override;
    void OnLayoutChanged(CefRefPtr<CefView> view, const CefRect& newBounds) override;

    // 当前页面弹出新窗口时此方法被执行
    bool OnPopupBrowserViewCreated(CefRefPtr<CefBrowserView> browser_view, CefRefPtr<CefBrowserView> popup_browser_view, bool is_devtools) override;

    WindowDelegate(const WindowDelegate&) = delete;
    WindowDelegate& operator=(const WindowDelegate&) = delete;
    CefRefPtr<CefWindow> win;
private:
    CefRefPtr<CefBrowserView> createView(std::string& url);
    nlohmann::json config;
    bool isDevTool = false;
    bool hasDockView = false;
    CefRefPtr<CefBrowserView> view;
    std::vector<CefRefPtr<CefBrowserView>> overlayViews;
    std::vector<CefInsets> dockInsets;
    std::vector<CefRefPtr<CefOverlayController>> overlayController;
    IMPLEMENT_REFCOUNTING(WindowDelegate);
};

