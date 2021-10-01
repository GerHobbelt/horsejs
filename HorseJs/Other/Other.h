#pragma once
#include "cef/include/cef_app.h"
class Other :
    public CefApp
{
public:
    Other() = default;
private:
    IMPLEMENT_REFCOUNTING(Other);
    DISALLOW_COPY_AND_ASSIGN(Other);
};