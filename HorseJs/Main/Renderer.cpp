#include "Renderer.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include "../V8Handler/V8Handler.h"
void Renderer::OnWebKitInitialized()
{
    auto targetPath = std::filesystem::current_path();
    targetPath.append("extension.js");
    std::ifstream reader;
    reader.open(targetPath, std::ios::in);
    std::stringstream buffer;
    buffer << reader.rdbuf();
    reader.close();
    auto extensionCode = buffer.str();
    CefRefPtr<CefV8Handler> handler = new V8Handler();    
    CefRegisterExtension("horse/extension", extensionCode, handler);
}
void Renderer::OnBrowserDestroyed(CefRefPtr<CefBrowser> browser)
{
    std::cout << "allen";
}
void Renderer::OnFocusedNodeChanged(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefDOMNode> node)
{
    std::cout << "allen";
}
bool Renderer::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
{
    return false;
}
