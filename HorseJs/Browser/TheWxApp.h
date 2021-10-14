#pragma once
#include <wx/wx.h>
#include "include/cef_app.h"
class TheWxApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        //Bind(wxEVT_IDLE, &TheWxApp::OnIdle, this);
        return true;
    }
    void OnIdle(wxIdleEvent& event) {
        //CefRunMessageLoop();
        //CefShutdown();
    };
};
