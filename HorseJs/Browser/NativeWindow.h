#pragma once
#include "wx/nativewin.h"
#include "TopWindow.h"
#include <wx/timer.h>
#include "wx/msw/private.h"
#include "wx/msw/window.h"
class NativeWindow : public wxNativeWindow
{
public:
    explicit NativeWindow(HWND hwnd) : wxNativeWindow()
    {
        static int id = 9987;
        id += 1;
        parent = new TopWindow();
        //parent->Show();  //不能显示，显示就坏了醋了
        const wxRect r = wxRectFromRECT(wxGetWindowRect(hwnd));
        if (!CreateBase(parent, id, r.GetPosition(), r.GetSize(), 0, wxDefaultValidator, wxS("nativewindow"))) {
            return;
        }
        parent->AddChild(this);
        SubclassWin(hwnd);
        SetId(id);
        InheritAttributes();
        Bind(wxEVT_CLOSE_WINDOW, &NativeWindow::OnClose, this);
    };
    void OnClose(wxCloseEvent& event) {
        //if (event.CanVeto() && m_bFileNotSaved)
        //{
        //    if (wxMessageBox("The file has not been saved... continue closing?",
        //        "Please confirm",
        //        wxICON_QUESTION | wxYES_NO) != wxYES)
        //    {
        //        event.Veto();
        //        return;
        //    }
        //}
        Destroy();
    };
    virtual ~NativeWindow()
    {
        Disown();
    };
protected:
    WXLRESULT MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam) wxOVERRIDE
    {        
        WXLRESULT rc;
        if (m_oldWndProc)
            rc = ::CallWindowProc(m_oldWndProc, GetHwnd(), nMsg, wParam, lParam);
        else
            rc = ::DefWindowProc(GetHwnd(), nMsg, wParam, lParam);
        //WM_WINDOWPOSCHANGING        
        if (nMsg != WM_SYSCOMMAND) return rc;
        if (wParam != SC_CLOSE) return rc;        
        //this->parent->Destroy();
        return rc;
    }
private:
    wxWindow* parent;
};

//C:\wxWidgets-3.1.5\src\msw\window.cpp   2460行
