#pragma once
#include "include/wrapper/cef_message_router.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "DialogCallback.h"
class Dialog:public CefRunFileDialogCallback
{
public:
    Dialog() = delete;
    static bool ProcessMsg(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
    {
        std::string message_name = message->GetName();
        message_name.erase(0, message_name.find_first_of('_') + 1);
        CefBrowserHost::FileDialogMode mode;
        if (message_name == "openFile")
        {
            mode = FILE_DIALOG_OPEN;
            CefRefPtr<CefListValue> args = message->GetArgumentList();
            CefRefPtr<CefListValue> filterSrc = args->GetList(2);
            std::vector<CefString> filter;
            for (size_t i = 0; i < filterSrc->GetSize(); i++)
            {
                filter.push_back(filterSrc->GetString(i));
            }
            CefRefPtr<CefRunFileDialogCallback> dcb = new DialogCallback();
            browser->GetHost()->RunFileDialog(mode, args->GetString(0), args->GetString(1),filter, args->GetInt(3),dcb);
            CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create("Dialog_");
            CefRefPtr<CefListValue> msgArgs = msg->GetArgumentList();

            frame->SendProcessMessage(PID_RENDERER, msg);
        }
        else if (message_name == "openFolder")
        {
            mode = FILE_DIALOG_OPEN_FOLDER;
        }

        return true;
    }
};