#include "V8Handler.h"
bool V8Handler::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    if (name != "__callHorseFunc") return true;
    auto msgName = arguments[0]->GetStringValue();
    if (msgName == "native_registe_callback") {
        callBack = arguments[1];
        return true;
    }
    CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(msgName);
    CefRefPtr<CefListValue> msgBody = msg->GetArgumentList();
    if (arguments.size() > 1 && arguments[1]->IsString()) {
        msgBody->SetString(0, arguments[1]->GetStringValue());
    }
    CefRefPtr<CefV8Context> context = CefV8Context::GetCurrentContext();
    context.get()->GetFrame()->SendProcessMessage(PID_BROWSER, msg);
    return true;
};
