#include "SchemeHandler.h"
#include "include/wrapper/cef_helpers.h"
#include <fstream>
#include <filesystem>

SchemeHandler::SchemeHandler() :offset_(0)
{
}
bool SchemeHandler::Open(CefRefPtr<CefRequest> request, bool& handle_request, CefRefPtr<CefCallback> callback)
{
    DCHECK(!CefCurrentlyOn(TID_UI) && !CefCurrentlyOn(TID_IO));
    handle_request = true;
    bool handled = false;
    std::string url = request->GetURL();
    url.erase(0, 13); //ÒÆ³ý£ºhttp://horse/
    auto curWorkDir = std::filesystem::current_path();
    curWorkDir.append(url);
    
    std::ifstream reader;
    reader.open(curWorkDir, std::ios::in);
    std::stringstream buffer;
    buffer << reader.rdbuf();
    reader.close();
    data_ = buffer.str();
    auto ext = curWorkDir.extension().generic_string();
    if (ext == ".html") {
        mime_type_ = "text/html";
    }
    else if(ext == ".js")
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
    return true;
}

void SchemeHandler::GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl)
{
    CEF_REQUIRE_IO_THREAD();
    DCHECK(!data_.empty());
    response->SetHeaderByName("Access-Control-Allow-Origin", "*", true);
    response->SetMimeType(mime_type_);
    response->SetStatus(200);
    response_length = data_.length();
}

void SchemeHandler::Cancel()
{
    CEF_REQUIRE_IO_THREAD();
}

bool SchemeHandler::Read(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefResourceReadCallback> callback)
{
    DCHECK(!CefCurrentlyOn(TID_UI) && !CefCurrentlyOn(TID_IO));
    bool has_data = false;
    bytes_read = 0;
    if (offset_ < data_.length()) {
        int transfer_size = std::min(bytes_to_read, static_cast<int>(data_.length() - offset_));
        memcpy(data_out, data_.c_str() + offset_, transfer_size);
        offset_ += transfer_size;
        bytes_read = transfer_size;
        has_data = true;
    }
    return has_data;
}

