#include "Handler.h"
#include <sstream>
#include <string>

#include "include/base/cef_bind.h"
#include "include/cef_app.h"
#include "include/cef_parser.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"

namespace {
    Handler* g_instance = nullptr;
    std::string GetDataURI(const std::string& data, const std::string& mime_type) {
        return "data:" + mime_type + ";base64," + CefURIEncode(CefBase64Encode(data.data(), data.size()), false).ToString();
    }
}

Handler::Handler()
    : use_views_(true), is_closing_(false) {
    DCHECK(!g_instance);
    g_instance = this;
}

Handler::~Handler() {
    g_instance = nullptr;
}
// static
Handler* Handler::GetInstance() {
    return g_instance;
}

void Handler::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title)
{
    CEF_REQUIRE_UI_THREAD();
    if (use_views_)
    {
        CefRefPtr<CefBrowserView> browser_view = CefBrowserView::GetForBrowser(browser);
        if (browser_view)
        {
            CefRefPtr<CefWindow> window = browser_view->GetWindow();
            if (window) window->SetTitle(title);
        }
    }
    else if (!IsChromeRuntimeEnabled())
    {
        PlatformTitleChange(browser, title);
    }
}

void Handler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
    browser_list_.push_back(browser);
}

bool Handler::DoClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
    if (browser_list_.size() == 1)
    {
        is_closing_ = true;
    }

    return false;
}

void Handler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();

    // Remove from the list of existing browsers.
    BrowserList::iterator bit = browser_list_.begin();
    for (; bit != browser_list_.end(); ++bit) {
        if ((*bit)->IsSame(browser)) {
            browser_list_.erase(bit);
            break;
        }
    }

    if (browser_list_.empty()) {
        // All browser windows have closed. Quit the application message loop.
        CefQuitMessageLoop();
    }
}

void Handler::OnLoadError(CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    ErrorCode errorCode,
    const CefString& errorText,
    const CefString& failedUrl) {
    CEF_REQUIRE_UI_THREAD();

    // Allow Chrome to show the error page.
    if (IsChromeRuntimeEnabled())
        return;

    // Don't display an error for downloaded files.
    if (errorCode == ERR_ABORTED)
        return;

    // Display a load error message using a data: URI.
    std::stringstream ss;
    ss << "<html><body bgcolor=\"white\">"
        "<h2>Failed to load URL "
        << std::string(failedUrl) << " with error " << std::string(errorText)
        << " (" << errorCode << ").</h2></body></html>";

    frame->LoadURL(GetDataURI(ss.str(), "text/html"));
}

void Handler::CloseAllBrowsers(bool force_close) {
    if (!CefCurrentlyOn(TID_UI)) {
        CefPostTask(TID_UI, base::Bind(&Handler::CloseAllBrowsers, this, force_close));
        return;
    }
    if (browser_list_.empty())
        return;
    BrowserList::const_iterator it = browser_list_.begin();
    for (; it != browser_list_.end(); ++it)
        (*it)->GetHost()->CloseBrowser(force_close);
}
bool Handler::OnDragEnter(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDragData> dragData, CefDragHandler::DragOperationsMask mask)
{
    CEF_REQUIRE_UI_THREAD();
    return false;
}
void Handler::OnDraggableRegionsChanged(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const std::vector<CefDraggableRegion>& regions)
{
    CefRefPtr<CefBrowserView> browser_view = CefBrowserView::GetForBrowser(browser);
    if (browser_view)
    {
        CefRefPtr<CefWindow> window = browser_view->GetWindow();
        if (window) window->SetDraggableRegions(regions);
    }
}

bool Handler::IsChromeRuntimeEnabled() {
    static int value = -1;
    if (value == -1) {
        CefRefPtr<CefCommandLine> command_line = CefCommandLine::GetGlobalCommandLine();
        value = command_line->HasSwitch("enable-chrome-runtime") ? 1 : 0;
    }
    return value == 1;
}

void Handler::PlatformTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title)
{
    //todo 
    CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
    if (hwnd)
        SetWindowText(hwnd, std::wstring(title).c_str());
}
