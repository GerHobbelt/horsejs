#include "Renderer.h"

void Renderer::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) {
    CefRefPtr<CefV8Value> globalObject = context->GetGlobal();
    v8Handler = new V8Handler();
    CefRefPtr<CefV8Value> nativeCall = CefV8Value::CreateFunction("nativeCall", v8Handler);
    globalObject->SetValue("nativeCall", nativeCall, V8_PROPERTY_ATTRIBUTE_READONLY);
}
