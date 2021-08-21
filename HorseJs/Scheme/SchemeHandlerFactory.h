#pragma once
#include "include/cef_scheme.h"
#include "include/cef_browser.h"
#include "include/cef_callback.h"
#include "include/cef_frame.h"
#include "include/cef_request.h"
#include "include/cef_resource_handler.h"
#include "include/cef_response.h"
#include "include/cef_scheme.h"
#include "include/wrapper/cef_helpers.h"
#include "SchemeHandler.h"

class SchemeHandlerFactory :
    public CefSchemeHandlerFactory
{
public:
    SchemeHandlerFactory() = default;
    CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& scheme_name, CefRefPtr<CefRequest> request) OVERRIDE
    {
        CEF_REQUIRE_IO_THREAD();
        return new SchemeHandler();
    };
    IMPLEMENT_REFCOUNTING(SchemeHandlerFactory);
    DISALLOW_COPY_AND_ASSIGN(SchemeHandlerFactory);
};

