#include "Renderer.h"
#include <iostream>
#include <fstream>
#include <filesystem>
Renderer::Renderer() :v8Handler(new V8Handler())
{
}
void Renderer::OnWebKitInitialized()
{
    //auto targetPath = std::filesystem::current_path();
    //targetPath.append("extension.js");
    //std::ifstream reader;
    //reader.open(targetPath, std::ios::in);
    //std::stringstream buffer;
    //buffer << reader.rdbuf();
    //reader.close();
    //auto extensionCode = buffer.str();
    //CefRefPtr<CefV8Handler> handler = new V8Handler();    
    //CefRegisterExtension("horse/extension", extensionCode, v8Handler);
}
void Renderer::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
    CefRefPtr<CefV8Value> object = context->GetGlobal();
    CefRefPtr<CefV8Handler> handler = new V8Handler(); 
    CefRefPtr<CefV8Value> func = CefV8Value::CreateFunction("__callHorseFunc", handler);
    object->SetValue("__callHorseFunc", func, V8_PROPERTY_ATTRIBUTE_NONE);

    auto targetPath = std::filesystem::current_path();
    targetPath.append("app//extension.js");
    std::ifstream reader;
    reader.open(targetPath, std::ios::in);
    std::stringstream buffer;
    buffer << reader.rdbuf();
    reader.close();
    auto jsCode = buffer.str();
    //todo µ÷ÊÔÎÊÌâ
    frame->ExecuteJavaScript(jsCode,"http://horse/extension.js", 1);
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
    auto args = message->GetArgumentList();
    std::string script = "horse.emitEvent('" + message_name + "'," + args->GetString(0).ToString() +");";
    frame->ExecuteJavaScript(script, frame->GetURL(), 0);
    return true;
}
