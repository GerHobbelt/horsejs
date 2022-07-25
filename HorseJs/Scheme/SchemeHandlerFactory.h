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
#include <iostream>

class SchemeHandlerFactory :
    public CefSchemeHandlerFactory
{
public:
    SchemeHandlerFactory() = default;
    CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& scheme_name, CefRefPtr<CefRequest> request) override
    {
        CEF_REQUIRE_IO_THREAD();
        //return new SchemeHandler();
        std::string url = request->GetURL();
        url.erase(0, 13); //移除：http://horse/
        auto paramIndex = url.find_first_of('?');
        if (paramIndex != std::string::npos) url.erase(paramIndex);
        std::filesystem::path targetPath = std::filesystem::current_path();
        targetPath.append(url);
        //LOG(ERROR) << targetPath.generic_u8string();
        if (!std::filesystem::exists(targetPath)) {
            std::cout << "试图加载" << targetPath << "，但找不到这个文件";
        }
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
        else if (ext == ".png")
        {
            mime_type_ = "image/png";
        }
        else if (ext == ".jpg" || ext == ".jpeg")
        {
            mime_type_ = "image/jpeg";
        }
        else if (ext == ".gif")
        {
            mime_type_ = "image/gif";
        }
        else
        {
            mime_type_ = "application/*";
        }
        auto stream = CefStreamReader::CreateForFile(targetPath.generic_wstring());
        return new CefStreamResourceHandler(mime_type_, stream);
    };
    IMPLEMENT_REFCOUNTING(SchemeHandlerFactory);
    DISALLOW_COPY_AND_ASSIGN(SchemeHandlerFactory);
};

