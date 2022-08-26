#include "Renderer.h"
#include "ReleaseCallback.h"

void Renderer::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) {
    CefRefPtr<CefV8Value> globalObject = context->GetGlobal();
    v8Handler = new V8Handler();
    CefRefPtr<CefV8Value> nativeCall = CefV8Value::CreateFunction("nativeCall", v8Handler);
    globalObject->SetValue("nativeCall", nativeCall, V8_PROPERTY_ATTRIBUTE_READONLY);
}

bool Renderer::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
{
    CefString messageName = message->GetName();
    CefRefPtr<CefListValue> args = message->GetArgumentList();
    CefRefPtr<CefV8Context> context = frame->GetV8Context();
    context->Enter();
    CefRefPtr<CefV8Value> messageNameV8 = CefV8Value::CreateString(messageName);
    CefV8ValueList argsForJs;
    argsForJs.push_back(messageNameV8);
    if (args->GetType(0) == CefValueType::VTYPE_STRING) {
        CefString result = args->GetString(0);
        CefRefPtr<CefV8Value> resultV8 = CefV8Value::CreateString(result);
        argsForJs.push_back(resultV8);
    }
    else if (args->GetType(0) == CefValueType::VTYPE_BINARY) {
        CefRefPtr<CefBinaryValue> data = args->GetBinary(0);
        size_t size = data->GetSize();
        unsigned char* result = new unsigned char[size];
        data->GetData(result, size, 0);
        CefRefPtr<CefV8ArrayBufferReleaseCallback> cb = new ReleaseCallback();
        CefRefPtr<CefV8Value> resultV8 = CefV8Value::CreateArrayBuffer(result, size, cb);
        argsForJs.push_back(resultV8);
    }
    v8Handler->callBack->ExecuteFunction(nullptr, argsForJs);
    context->Exit();
    return true;
}
