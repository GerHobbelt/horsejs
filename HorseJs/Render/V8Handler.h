#pragma once
#include "include/cef_v8.h"
class V8Handler :public CefV8Handler
{
public:
    V8Handler() = default;
    CefRefPtr<CefV8Value> callBack;
    virtual bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception) override;
private:
    IMPLEMENT_REFCOUNTING(V8Handler);
};

