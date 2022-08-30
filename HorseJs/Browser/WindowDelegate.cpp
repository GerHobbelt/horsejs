#include "WindowDelegate.h"
#include "TopWindow.h"


void WindowDelegate::OnWindowCreated(CefRefPtr<CefWindow> window)
{
    window->AddChildView(browser_view_);
    auto config = Config::get();
    auto autoShowFirstWindow = config["autoShowFirstWindow"].get<bool>();
    if (autoShowFirstWindow) {
        window->Show();
        //TopWindow* win = new TopWindow();
        //win->Show();
        HWND hwnd = window->GetWindowHandle();
        nativeWindow = new NativeWindow(hwnd);
    }
    window->CenterWindow(window->GetSize());
    CefRefPtr<CefImage> image = CefImage::CreateImage();
    PrepareIcon(image, 1.0f, "icon1.png");
    PrepareIcon(image, 2.0f, "icon2.png");
    window->SetWindowAppIcon(image);
    browser_view_->RequestFocus();
}
//bool WindowDelegate::CanClose(CefRefPtr<CefWindow> window)
//{
//    CefRefPtr<CefBrowser> browser = browser_view_->GetBrowser();
//    if (browser) {
//        return browser->GetHost()->TryCloseBrowser();
//    }        
//    return true;
//}

CefSize WindowDelegate::GetPreferredSize(CefRefPtr<CefView> view){
    return getSizeConfig("startSize");
}
CefSize WindowDelegate::GetMinimumSize(CefRefPtr<CefView> view) {
    return getSizeConfig("miniSize");
}
CefSize WindowDelegate::GetMaximumSize(CefRefPtr<CefView> view) {
    return getSizeConfig("maxSize");
}
CefSize WindowDelegate::getSizeConfig(std::string_view configName) {
    json miniSize = Config::get()["sizeConfig"][std::string(configName)];
    int width = miniSize["width"].get<int>();
    int height = miniSize["height"].get<int>();
    return CefSize(width, height);
}
void WindowDelegate::PrepareIcon(CefRefPtr<CefImage> image, double scale_factor, const std::string& name) {
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