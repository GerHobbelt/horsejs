#pragma once
#include "include/cef_v8.h"
#include "../Main/Browser.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
class V8Handler :
    public CefV8Handler
{
public:
    V8Handler() = default;
    virtual bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception) OVERRIDE
    {
        if (name == "jsFunc") 
        {
            CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(arguments[0]->GetStringValue());
            //CefRefPtr<CefListValue> args = msg->GetArgumentList();
            //args->SetString(0, arguments[0]->GetStringValue());
            CefRefPtr<CefV8Context> context = CefV8Context::GetCurrentContext();
            context.get()->GetFrame()->SendProcessMessage(PID_BROWSER, msg);
            return true;
        }
        return false;
    };
private:
    IMPLEMENT_REFCOUNTING(V8Handler);
};