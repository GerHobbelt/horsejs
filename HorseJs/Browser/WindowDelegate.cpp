#include "WindowDelegate.h"
#include "TopWindow.h"


void WindowDelegate::OnWindowCreated(CefRefPtr<CefWindow> window)
{
    window->AddChildView(browser_view_);
    auto config = Config::get();
    HWND hwnd = window->GetWindowHandle();
    if (!isDevWindow) nativeWindow = new NativeWindow(hwnd,window);

    HICON hIcon = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(102), IMAGE_ICON, 32, 32, 0);
    LRESULT res = SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    auto autoShowFirstWindow = config["firstWindow"]["autoShow"].get<bool>();
    if (autoShowFirstWindow || isDevWindow) {
        window->Show();
        window->CenterWindow(window->GetSize());
        browser_view_->RequestFocus();
    }
    //CefRefPtr<CefImage> image = CefImage::CreateImage();
    //PrepareIcon(image, 1.0f, "icon1.png");
    //PrepareIcon(image, 2.0f, "icon2.png");
    //window->SetWindowAppIcon(image);
}
bool WindowDelegate::CanClose(CefRefPtr<CefWindow> window)
{
    CefRefPtr<CefBrowser> browser = browser_view_->GetBrowser();
    if (browser) {
        browser->GetHost()->TryCloseBrowser();
        if(!isDevWindow) nativeWindow->parent->Close();
    }        
    return true;
}

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
    json miniSize = Config::get()["firstWindow"]["sizeConfig"][std::string(configName)];
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