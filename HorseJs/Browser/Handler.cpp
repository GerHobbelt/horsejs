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
#include "MsgHandler/Window.h"
#include "MsgHandler/Dialog.h"
#include "MsgHandler/Shell.h"
#include "MsgHandler/Info.h"
#include "MsgHandler/Clipboard.h"
#include "MsgHandler/File.h"
#include "MsgHandler/Path.h"
#include "MsgHandler/System.h"
#include "MsgHandler/Menu.h"

namespace {
    Handler* g_instance = nullptr;
    std::string GetDataURI(const std::string& data, const std::string& mime_type) 
    {
        return "data:" + mime_type + ";base64," + CefURIEncode(CefBase64Encode(data.data(), data.size()), false).ToString();
    }
}



Handler::Handler() : use_views_(true), is_closing_(false) {
    DCHECK(!g_instance);
    g_instance = this;
}

Handler::~Handler() {
    g_instance = nullptr;
}

bool Handler::OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& target_url, const CefString& target_frame_name,
    WindowOpenDisposition target_disposition,
    bool user_gesture,
    const CefPopupFeatures& popupFeatures,
    CefWindowInfo& windowInfo,
    CefRefPtr<CefClient>& client,
    CefBrowserSettings& settings,
    CefRefPtr<CefDictionaryValue>& extra_info,
    bool* no_javascript_access)
{
    //MainContext::Get()->GetRootWindowManager()->CreateRootWindowAsPopup(!is_devtools, is_osr(), popupFeatures, windowInfo, client, settings);
    //switch (target_disposition)
    //{
    //case WOD_NEW_FOREGROUND_TAB:
    //case WOD_NEW_BACKGROUND_TAB:
    //case WOD_NEW_POPUP:
    //case WOD_NEW_WINDOW:
    //    browser->GetMainFrame()->LoadURL(target_url);
    //    return true; //Í£Ö¹´´½¨
    //}

    return false;
}
// static
Handler* Handler::GetInstance() {
    return g_instance;
}

void Handler::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title)
{
    CEF_REQUIRE_UI_THREAD();
    CefRefPtr<CefBrowserView> browser_view = CefBrowserView::GetForBrowser(browser);
    if (browser_view)
    {
        CefRefPtr<CefWindow> window = browser_view->GetWindow();
        if (window) window->SetTitle(title);
    }
}

void Handler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
    browser_list_.push_back(browser);
    //if (!message_router_) {
    //    CefMessageRouterConfig config;
    //    message_router_ = CefMessageRouterBrowserSide::Create(config);
    //    message_router_->AddHandler(*(it), false);
    //}
}

bool Handler::DoClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
    if (browser_list_.size() == 1)
    {
        is_closing_ = true;
    }
    return false;
}

void Handler::OnBeforeClose(CefRefPtr<CefBrowser> browser) 
{
    CEF_REQUIRE_UI_THREAD();
    BrowserList::iterator bit = browser_list_.begin();
    for (; bit != browser_list_.end(); ++bit) {
        if ((*bit)->IsSame(browser)) {
            browser_list_.erase(bit);
            break;
        }
    }
    if (browser_list_.empty()) {
        //auto it = message_handler_set_.begin();
        //for (; it != message_handler_set_.end(); ++it) {
        //    message_router_->RemoveHandler(*(it));
        //    delete *(it);
        //}
        //message_handler_set_.clear();
        //message_router_ = nullptr;
        CefQuitMessageLoop();
    }
}

void Handler::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl) 
{
    CEF_REQUIRE_UI_THREAD();
    if (IsChromeRuntimeEnabled())
        return;
    if (errorCode == ERR_ABORTED)
        return;
    std::stringstream ss;
    ss << "<html><body bgcolor=\"white\">"
        "<h2>Failed to load URL "
        << std::string(failedUrl) << " with error " << std::string(errorText)
        << " (" << errorCode << ").</h2></body></html>";
    frame->LoadURL(GetDataURI(ss.str(), "text/html"));
}
void Handler::CloseAllBrowsers(bool force_close) {
    if (!CefCurrentlyOn(TID_UI)) {
        //CefPostTask(TID_UI, base::Bind(&Handler::CloseAllBrowsers, this, force_close));
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

void Handler::OnStatusMessage(CefRefPtr<CefBrowser> browser, const CefString& value)
{
    return;
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
bool Handler::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) 
{
    CEF_REQUIRE_UI_THREAD();
    std::string message_name = message->GetName();
    if (message_name._Starts_with("Window"))
    {
        return Window::ProcessMsg(browser, frame, source_process, message);
    }
    else if(message_name._Starts_with("Dialog"))
    {
        return Dialog::ProcessMsg(browser, frame, source_process, message);
    }
    else if (message_name._Starts_with("Shell"))
    {
        return Shell::ProcessMsg(browser, frame, source_process, message);
    }
    else if (message_name._Starts_with("Info"))
    {
        return Info::ProcessMsg(browser, frame, source_process, message);
    }
    else if (message_name._Starts_with("Clipboard"))
    {
        return Clipboard::ProcessMsg(browser, frame, source_process, message);
    }
    else if (message_name._Starts_with("File"))
    {
        return File::ProcessMsg(browser, frame, source_process, message);
    }
    else if (message_name._Starts_with("Path"))
    {
        return Path::ProcessMsg(browser, frame, source_process, message);
    }
    else if (message_name._Starts_with("System"))
    {
        return System::ProcessMsg(browser, frame, source_process, message);
    }
    else if (message_name._Starts_with("Menu"))
    {
        return Menu::ProcessMsg(browser, frame, source_process, message);
    }
    return false;
}
