#pragma once
#include "include/cef_client.h"
#include <list>
#include <set>
#include "include/wrapper/cef_message_router.h"
#include "../Common/json.hpp"
#include <wx/wx.h>
#include <wx/event.h>
#include <wx/notifmsg.h>
using nlohmann::json;
class Handler :
    public CefClient,
    public CefDisplayHandler,
    public CefLifeSpanHandler,
    public CefLoadHandler,
    public CefDragHandler,
    public CefJSDialogHandler,
    public CefContextMenuHandler
{
public:
    explicit Handler();
    ~Handler();
    static Handler* GetInstance();

    //json menuData;
    //CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() override { return this; }
    //virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model) override;
    //virtual bool OnContextMenuCommand(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, int command_id, EventFlags event_flags) override;
    //virtual void OnContextMenuDismissed(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame) override;


    virtual CefRefPtr<CefJSDialogHandler> GetJSDialogHandler() override { return this; }
    virtual bool OnJSDialog(CefRefPtr<CefBrowser> browser, const CefString& origin_url, JSDialogType dialog_type, const CefString& message_text, const CefString& default_prompt_text, CefRefPtr<CefJSDialogCallback> callback, bool& suppress_message) override;

    CefRefPtr<CefDragHandler> GetDragHandler() override { return this; }
    virtual bool OnDragEnter(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDragData> dragData, CefDragHandler::DragOperationsMask mask) override;
    virtual void OnDraggableRegionsChanged(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const std::vector<CefDraggableRegion>& regions) override;

    virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() override { return this; }
    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override { return this; }

    virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) override;
    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
    virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;
    virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;
    virtual void OnStatusMessage(CefRefPtr<CefBrowser> browser, const CefString& value) override;
    bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) override;
    virtual void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl) override;
    virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& target_url, const CefString& target_frame_name,
        WindowOpenDisposition target_disposition,
        bool user_gesture,
        const CefPopupFeatures& popupFeatures,
        CefWindowInfo& windowInfo,
        CefRefPtr<CefClient>& client,
        CefBrowserSettings& settings,
        CefRefPtr<CefDictionaryValue>& extra_info,
        bool* no_javascript_access) override;
    void CloseAllBrowsers(bool force_close);
    bool IsClosing() const { return is_closing_; }
    static bool IsChromeRuntimeEnabled();
    CefRefPtr<CefMessageRouterBrowserSide> message_router_;
    std::set<CefMessageRouterBrowserSide::Handler*> message_handler_set_;
private:
    const bool use_views_;
    wxTextEntryDialog* dlg;
    typedef std::list<CefRefPtr<CefBrowser>> BrowserList;
    BrowserList browser_list_;
    bool is_closing_;
    void notifyClick(wxCommandEvent& event);
    IMPLEMENT_REFCOUNTING(Handler);
};

