#include "Handler.h"
#include <sstream>
#include <string>
#include <wx/msgdlg.h>
#include <wx/windowptr.h>
#include <wx/event.h>
#include <wx/thread.h>



#include "include/base/cef_bind.h"
#include "include/cef_app.h"
#include "include/cef_parser.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"
#include "../Common/Config.h"

#include "MsgHandler/Window.h"
#include "MsgHandler/Dialog.h"
#include "MsgHandler/Info.h"
#include "MsgHandler/Clipboard.h"
#include "MsgHandler/File.h"
#include "MsgHandler/Path.h"
#include "MsgHandler/System.h"
#include "MsgHandler/Menu.h"
#include "MsgHandler/Tray.h"
#include "MsgHandler/Plugin.h"
#include "MsgHandler/Db.h"

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

/// <summary>
/// 
/// </summary>
/// <param name="browser"></param>
/// <param name="origin_url"></param>
/// <param name="dialog_type"></param>
/// <param name="message_text"></param>
/// <param name="default_prompt_text"></param>
/// <param name="callback"></param>
/// <param name="suppress_message">
/// 如果这个参数被设置为true，并且函数返回值为false，将阻止页面打开JS的弹出窗口。 
/// 如果这个参数被设置为false，并且函数返回值也是false，页面将会打开这个JS弹出窗口。
/// </param>
/// <returns></returns>
bool Handler::OnJSDialog(CefRefPtr<CefBrowser> browser, const CefString& origin_url, JSDialogType dialog_type, const CefString& message_text, const CefString& default_prompt_text, CefRefPtr<CefJSDialogCallback> callback, bool& suppress_message)
{
    HWND winHandle = browser->GetHost()->GetWindowHandle();
    auto parent = wxFindWinFromHandle(winHandle);
    auto config = Config::get();
    auto appName = wxString::FromUTF8(config["appName"].get<std::string>());
    auto msg = message_text.ToWString();
    suppress_message = true;
    if (dialog_type == JSDIALOGTYPE_ALERT) {
        wxMessageDialog dialog(parent, msg, appName, wxOK | wxCENTRE);
        dialog.ShowModal();
    }
    else if (dialog_type == JSDIALOGTYPE_CONFIRM) {
        wxMessageDialog dialog(parent, msg, appName, wxOK | wxCANCEL);
        auto result = dialog.ShowModal();  //(()=>{var a = confirm('测试');console.log(a)})();
        if (result == wxID_OK)
        {
            callback->Continue(true, "");
        }
        else
        {
            callback->Continue(false, "");
        }
    }
    else if (dialog_type == JSDIALOGTYPE_PROMPT) {
        wxMessageDialog dialog(parent, "抱歉，目前暂时不支持prompt弹窗", appName, wxOK | wxCENTRE);
        dialog.ShowModal();
        //CEF_REQUIRE_UI_THREAD();
        //wxGetTextFromUser(msg, appName, wxEmptyString, parent);
        //suppress_message = false;        
        //CefPostTask(TID_UI, base::BindOnce(&readFile, path, bufferSize, frame, msgName));
        //dlg = new wxTextEntryDialog(parent, msg, appName, wxEmptyString);
        //dlg->Show();
        //dlg->Bind()
        //wxMutex mutex;
        //wxCondition condition(mutex);
        //int i = 0;
        //parent->GetEventHandler()->CallAfter([&]()
        //    {
                //wxTextEntryDialog dlg(parent, msg, appName, wxEmptyString);
                //auto result = wxGetTextFromUser(msg, appName, wxEmptyString, parent);
                //callback->Continue(true, result.ToStdString());
                //if (dlg.ShowModal() == wxID_OK)
                //{
                //    auto result = dlg.GetValue();
                //    callback->Continue(true, result.ToStdString());
                //}
                //else
                //{
                //    CefString result;
                //    callback->Continue(false,result);
                //}
                //i = 1;
                //condition.Broadcast();
            //});
        //condition.Wait();
        //condition.Broadcast();
        //condition.Wait([&] {return i == 1; });
        //todo 这里有问题
        //auto result = wxGetTextFromUser(msg, appName, wxEmptyString, parent);
        //callback->Continue(true, result.ToStdString());
    }
    return false;
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
        //todo 关闭窗口不退出应用
        wxTheApp->Exit();
        //CefQuitMessageLoop();
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
        "<h2>加载页面失败："
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
//void Handler::OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model)
//{
//    model->Clear();
//    if (menuData.is_null()) return;
//    int menuIdStartIndex = 666;
//    for (auto& menuItem : menuData)
//    {
//        //todo 不支持子菜单
//        model->AddItem(menuIdStartIndex, menuItem["name"].get<std::string>());
//        menuIdStartIndex += 1;
//    }
//}
//bool Handler::OnContextMenuCommand(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, int command_id, EventFlags event_flags)
//{
//    switch (command_id)
//    {
//    default:
//        break;
//    }
//    return true;
//}
//void Handler::OnContextMenuDismissed(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame)
//{
//    menuData.clear();
//}
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
    else if (message_name._Starts_with("Tray"))
    {
        return Tray::ProcessMsg(browser, frame, source_process, message);
    }
    else if (message_name._Starts_with("Plugin"))
    {
        return Plugin::ProcessMsg(browser, frame, source_process, message);
    }
    else if (message_name._Starts_with("Db"))
    {
        return Db::ProcessMsg(browser, frame, source_process, message);
    }
    return false;
}
