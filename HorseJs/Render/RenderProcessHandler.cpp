#include "RenderProcessHandler.h"
#include "ReleaseCallback.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"

void RenderProcessHandler::OnBrowserCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDictionaryValue> extraInfo) {
    winId = extraInfo->GetInt("winId");
    curViewId = extraInfo->GetInt("curViewId");
    mainViewId = extraInfo->GetInt("mainViewId");
}
void RenderProcessHandler::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) {
    CefRefPtr<CefV8Value> globalObject = context->GetGlobal();
    v8Handler = new V8Handler();
    CefRefPtr<CefV8Value> nativeCall = CefV8Value::CreateFunction("__nativeCall", v8Handler);
    globalObject->SetValue("__nativeCall", nativeCall, V8_PROPERTY_ATTRIBUTE_READONLY);
    globalObject->SetValue("__winId", CefV8Value::CreateInt(this->winId), V8_PROPERTY_ATTRIBUTE_READONLY);
    globalObject->SetValue("__curViewId", CefV8Value::CreateInt(this->curViewId), V8_PROPERTY_ATTRIBUTE_READONLY);
    globalObject->SetValue("__mainViewId", CefV8Value::CreateInt(this->mainViewId), V8_PROPERTY_ATTRIBUTE_READONLY);
}

bool RenderProcessHandler::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
{
    CefString messageName = message->GetName();
    //CefRefPtr<CefListValue> args = message->GetArgumentList();
    CefRefPtr<CefV8Context> context = frame->GetV8Context();
    context->Enter();
    CefRefPtr<CefV8Value> messageStr = CefV8Value::CreateString(messageName);
    CefV8ValueList argsForJs;
    argsForJs.push_back(messageStr);
    //todo 应该不需要传送数据流给客户端
    //if (args->GetType(0) == CefValueType::VTYPE_STRING) {
        //CefString result = args->GetString(0);
        //CefRefPtr<CefV8Value> resultV8 = CefV8Value::CreateString(result);
        //argsForJs.push_back(resultV8);
    //}
    v8Handler->callBack->ExecuteFunction(nullptr, argsForJs);
    context->Exit();
    return true;
}