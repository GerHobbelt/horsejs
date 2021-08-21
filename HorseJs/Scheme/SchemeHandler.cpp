#include "SchemeHandler.h"
#include "include/wrapper/cef_helpers.h"

SchemeHandler::SchemeHandler() :offset_(0)
{
}
bool SchemeHandler::Open(CefRefPtr<CefRequest> request, bool& handle_request, CefRefPtr<CefCallback> callback)
{
    DCHECK(!CefCurrentlyOn(TID_UI) && !CefCurrentlyOn(TID_IO));
    handle_request = true;
    bool handled = false;
    std::string url = request->GetURL();
    if (strstr(url.c_str(), "handler.html") != nullptr) {
        data_ = R"(<html><head>
<title>Client Scheme Handler</title>
<style>html,body{margin:0px;padding:0px} 
.draggable { -webkit-app-region: drag; height: 60px; background-color: blue; }
.nondraggable { -webkit-app-region: no-drag; width: 100px; height:60px; background-color: red;float:right;}</style></head>
<body style="background:#fff">
  <div class="draggable">
    <div class="nondraggable"></div>
  </div>
    <input id="a" type="text" />
<input id="b" type="text" />
</body></html>)";
        handled = true;
        mime_type_ = "text/html";
    }
    return handled;
}

void SchemeHandler::GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl)
{
    CEF_REQUIRE_IO_THREAD();
    DCHECK(!data_.empty());
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

