#include "Renderer.h"
#include <iostream>
#include <fstream>
#include <filesystem>
Renderer::Renderer() :v8Handler(new V8Handler())
{
}
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
    CefRegisterExtension("horse/extension", extensionCode, v8Handler);
}
void Renderer::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
    CefRefPtr<CefV8Value> object = context->GetGlobal();
    CefRefPtr<CefV8Value> func = CefV8Value::CreateFunction("__horseFuncCallBack", v8Handler);
    object->SetValue("__horseFuncCallBack", func, V8_PROPERTY_ATTRIBUTE_NONE);
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
    std::string message_name = message->GetName();
    if (message_name._Starts_with("Dialog"))
    {
        return DialogR::ProcessMsg(browser, frame, source_process, message);
    }
    else if (message_name._Starts_with("Window"))
    {

    }
    return false;
}
