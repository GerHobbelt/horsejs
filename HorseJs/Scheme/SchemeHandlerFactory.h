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
#include "include/wrapper/cef_stream_resource_handler.h"
#include <fstream>
#include <filesystem>

class SchemeHandlerFactory :
    public CefSchemeHandlerFactory
{
public:
    SchemeHandlerFactory() = default;
    CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& scheme_name, CefRefPtr<CefRequest> request) OVERRIDE
    {
        CEF_REQUIRE_IO_THREAD();
        //return new SchemeHandler();
        std::string url = request->GetURL();
        url.erase(0, 13); //ÒÆ³ý£ºhttp://horse/
        std::filesystem::path targetPath = std::filesystem::current_path();
        targetPath.append(url);
        auto ext = targetPath.extension().generic_string();
        std::string mime_type_;
        if (ext == ".html") {
            mime_type_ = "text/html";
        }
        else if (ext == ".js")
        {
            mime_type_ = "text/javascript";
        }
        else if (ext == ".css")
        {
            mime_type_ = "text/css";
        }
        else if (ext == ".json")
        {
            mime_type_ = "application/json";
        }
        else if (ext == ".svg")
        {
            mime_type_ = "image/svg+xml";
        }
        else
        {
            mime_type_ = "application/*";
        }
        auto stream = CefStreamReader::CreateForFile(targetPath.generic_string());
        return new CefStreamResourceHandler(mime_type_, stream);
    };
    IMPLEMENT_REFCOUNTING(SchemeHandlerFactory);
    DISALLOW_COPY_AND_ASSIGN(SchemeHandlerFactory);
};

