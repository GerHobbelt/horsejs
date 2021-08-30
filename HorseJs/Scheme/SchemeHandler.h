#pragma once
#include "include/cef_resource_handler.h"
class SchemeHandler :
    public CefResourceHandler
{
public:
    SchemeHandler();
    bool Open(CefRefPtr<CefRequest> request, bool& handle_request, CefRefPtr<CefCallback> callback) OVERRIDE;
    void GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl) OVERRIDE;
    bool Read(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefResourceReadCallback> callback) OVERRIDE;
    void Cancel() OVERRIDE;
private:
    std::string data_;
    std::string mime_type_;
    size_t offset_;

    IMPLEMENT_REFCOUNTING(SchemeHandler);
    DISALLOW_COPY_AND_ASSIGN(SchemeHandler);
};

