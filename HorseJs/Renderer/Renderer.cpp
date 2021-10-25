#include "Renderer.h"
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
    std::filesystem::path targetPath = std::filesystem::current_path();
    targetPath.append("extension.js");
    //LOG(ERROR) << targetPath;
    std::ifstream reader;
    reader.open(targetPath, std::ios::in);
    std::stringstream buffer;
    buffer << reader.rdbuf();
    reader.close();
    auto jsCode = buffer.str();
    //LOG(ERROR) << jsCode;
    frame->ExecuteJavaScript(jsCode,"http://horse/extension.js", 1);
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
    std::string message_name = message->GetName();
    auto args = message->GetArgumentList();
    if (args->GetType(0) == CefValueType::VTYPE_STRING) {
        std::string script = "horse.eventer.emitEvent('" + message_name + "'," + args->GetString(0).ToString() + ");";
        frame->ExecuteJavaScript(script, frame->GetURL(), 0);
    } else if(args->GetType(0) == CefValueType::VTYPE_BINARY){
        CefRefPtr<CefBinaryValue> data = args->GetBinary(0);
        size_t size = data->GetSize();
        unsigned char* buffer = new unsigned char[size];
        data->GetData(buffer, size, 0);
        unsigned char testChar = buffer[600];
        CefRefPtr<CefV8ArrayBufferReleaseCallback> cb = new ReleaseCallback();
        CefRefPtr<CefV8Value> bufferArr = CefV8Value::CreateArrayBuffer(buffer,size,cb);
        CefV8ValueList args;
        args.push_back(bufferArr);
        v8Handler->callBack->ExecuteFunction(nullptr, args);
        delete[] buffer;
    }
    return true;
}
