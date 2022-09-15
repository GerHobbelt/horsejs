#pragma once
#include "include/views/cef_window.h"
#include "../../json/json.hpp"
#include <list>
class WindowDelegate : public CefWindowDelegate
{
public:
    explicit WindowDelegate(const nlohmann::json& config,const int id);
    int AddOverlayView(const nlohmann::json& overlayViewConfig);
    void removeView(int id);
    bool IsFrameless(CefRefPtr<CefWindow> window) override;
    void OnChildViewChanged(CefRefPtr<CefView> view, bool added, CefRefPtr<CefView> child);
    void OnWindowCreated(CefRefPtr<CefWindow> window) override;
    void OnWindowDestroyed(CefRefPtr<CefWindow> window) override;
    CefRect GetInitialBounds(CefRefPtr<CefWindow> window) override;
    bool CanClose(CefRefPtr<CefWindow> window) override;
    void OnLayoutChanged(CefRefPtr<CefView> view, const CefRect& newBounds) override;
    //void OnWindowChanged(CefRefPtr<CefView> view, bool added) override;
    WindowDelegate(const WindowDelegate&) = delete;
    WindowDelegate& operator=(const WindowDelegate&) = delete;
    CefRefPtr<CefWindow> win;
private:
    nlohmann::json config;
    bool isDevTool = false;
    int id;
    CefRefPtr<CefPanel> parentPanel;
    CefRefPtr<CefBrowserView> view;
    std::vector<CefRefPtr<CefBrowserView>> overlayViews;
    std::vector<std::vector<int>> dockInsets;
    std::vector<CefRefPtr<CefOverlayController>> overlayController;
    IMPLEMENT_REFCOUNTING(WindowDelegate);
};

