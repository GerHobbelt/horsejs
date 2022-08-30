#include "Renderer.h"
#include "include/wrapper/cef_helpers.h"
#include <iostream>
#include <fstream>
#include <filesystem>
Renderer::Renderer() :v8Handler(new V8Handler())
{
}
Renderer::~Renderer()
{
    delete v8Handler;
}
void Renderer::OnWebKitInitialized()
{
    //std::cout << "allen";
}
void Renderer::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
    CefRefPtr<CefV8Value> object = context->GetGlobal();
    CefRefPtr<CefV8Value> func = CefV8Value::CreateFunction("__callHorseFunc", v8Handler);
    object->SetValue("__callHorseFunc", func, V8_PROPERTY_ATTRIBUTE_NONE);
    //std::filesystem::path targetPath = std::filesystem::current_path();
    //targetPath.append("extension.js");
    //std::ifstream reader;
    //reader.open(targetPath, std::ios::in);
    //std::stringstream buffer;
    //buffer << reader.rdbuf();
    //reader.close();
    //auto jsCode = buffer.str();
    //frame->ExecuteJavaScript(jsCode,"http://horse/extension.js", 1);
}
void Renderer::OnBrowserDestroyed(CefRefPtr<CefBrowser> browser)
{
    //std::cout << "allen";
}
void Renderer::OnFocusedNodeChanged(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefDOMNode> node)
{
    //std::cout << "allen";
}
bool Renderer::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
{
    auto args = message->GetArgumentList();
    CefRefPtr<CefV8Context> context = frame->GetV8Context();    
    context->Enter();
    CefString messageName = message->GetName();
    CefRefPtr<CefV8Value> messageNameV8 = CefV8Value::CreateString(messageName);
    CefV8ValueList argsForJs;
    argsForJs.push_back(messageNameV8);
    if (args->GetType(0) == CefValueType::VTYPE_STRING) {
        CefString result = args->GetString(0);
        CefRefPtr<CefV8Value> resultV8 = CefV8Value::CreateString(result);
        argsForJs.push_back(resultV8);    
    } else if(args->GetType(0) == CefValueType::VTYPE_BINARY){
        CefRefPtr<CefBinaryValue> data = args->GetBinary(0);
        size_t size = data->GetSize();
        unsigned char* result = new unsigned char[size];
        data->GetData(result, size, 0);
        CefRefPtr<CefV8ArrayBufferReleaseCallback> cb = new ReleaseCallback();
        CefRefPtr<CefV8Value> resultV8 = CefV8Value::CreateArrayBuffer(result, size, cb);
        argsForJs.push_back(resultV8);
        //delete[] buffer;
    }
    v8Handler->callBack->ExecuteFunction(nullptr, argsForJs);
    context->Exit();
    return true;
}
