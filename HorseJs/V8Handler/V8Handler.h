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
            CefRefPtr<CefListValue> args = msg->GetArgumentList();
            for (size_t i = 1; i < arguments.size(); i++)
            {
                if (arguments[i]->IsString()) {
                    args->SetString(i-1, arguments[i]->GetStringValue());
                }else if (arguments[i]->IsInt()) {
                    args->SetInt(i - 1, arguments[i]->GetIntValue());
                } else if (arguments[i]->IsBool()) {
                    args->SetBool(i - 1, arguments[i]->GetBoolValue());
                } else if (arguments[i]->IsDouble()) {
                    args->SetDouble(i - 1, arguments[i]->GetBoolValue());
                } else if (arguments[i]->IsNull()) {
                    args->SetNull(i - 1);
                }
            }
            CefRefPtr<CefV8Context> context = CefV8Context::GetCurrentContext();
            context.get()->GetFrame()->SendProcessMessage(PID_BROWSER, msg);
            return true;
        }
        return false;
    };
private:
    IMPLEMENT_REFCOUNTING(V8Handler);
};