#pragma once
#include "include/views/cef_window_delegate.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "../Common/Config.h"
#include <fstream>
#include <filesystem>
class WindowDelegate :
    public CefWindowDelegate
{
public:
    explicit WindowDelegate(CefRefPtr<CefBrowserView> browser_view) : browser_view_(browser_view) {}

    void OnWindowCreated(CefRefPtr<CefWindow> window) OVERRIDE
    {
        window->AddChildView(browser_view_);
        auto config = Config::get();
        auto autoShowFirstWindow = config["autoShowFirstWindow"].get<bool>();
        if (autoShowFirstWindow) {
            window->Show();
        }
        CefSize size{ 800,600 };
        window->CenterWindow(size);
        CefRefPtr<CefImage> image = CefImage::CreateImage();
        PrepareIcon(image, 1.0f, "icon1.png");
        PrepareIcon(image, 2.0f, "icon2.png");
        window->SetWindowAppIcon(image);
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
    void PrepareIcon(CefRefPtr<CefImage> image, double scale_factor, const std::string& name) {
        auto curWorkDir = std::filesystem::current_path();
        curWorkDir.append(name);
        std::ifstream reader;
        reader.open(curWorkDir, std::ios::binary);
        std::stringstream buffer;
        buffer << reader.rdbuf();
        reader.close();
        std::string data = buffer.str();
        image->AddPNG(scale_factor, data.c_str(), data.size());
        
    }
    IMPLEMENT_REFCOUNTING(WindowDelegate);
    DISALLOW_COPY_AND_ASSIGN(WindowDelegate);

};

