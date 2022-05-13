#pragma once
#include "wx/nativewin.h"
#include "TopWindow.h"
#include <wx/timer.h>
#include "wx/msw/private.h"
#include "wx/msw/window.h"
class NativeWindow : public wxNativeWindow
{
public:
    explicit NativeWindow(HWND hwnd, CefRefPtr<CefWindow> window) : wxNativeWindow() ,hwnd(hwnd),window(window)
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
        window = nullptr;
        //Disown();
    };
    wxWindow* parent;
protected:

    WXLRESULT MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam) wxOVERRIDE
    {
        WXLRESULT result;
        if (nMsg == WM_SYSCOMMAND && wParam == 0xF060) {
            window->Close();
            return result;
        }
        if (!MSWHandleMessage(&result, nMsg, wParam, lParam)) {
            if (m_oldWndProc)
                result = ::CallWindowProc(m_oldWndProc, GetHwnd(), nMsg, wParam, lParam);
            else
                result = ::DefWindowProc(GetHwnd(), nMsg, wParam, lParam);
        }
        //if (nMsg == WM_SYSCOMMAND && wParam == 0xF060) {
        //    this->parent->Destroy();
        //    //LOG(ERROR) << GetHwnd()<<":"<<this->hwnd;
        //    SendMessage(this->hwnd,nMsg,wParam, lParam);
        //    //if (m_oldWndProc)
        //    //    result = ::CallWindowProc(m_oldWndProc, GetHwnd(), nMsg, wParam, lParam);
        //    //else
        //    //    result = ::DefWindowProc(GetHwnd(), nMsg, wParam, lParam);
        //}
        //else 
        //{
        //    if (!MSWHandleMessage(&result, nMsg, wParam, lParam)){
        //        if (m_oldWndProc)
        //            result = ::CallWindowProc(m_oldWndProc, GetHwnd(), nMsg, wParam, lParam);
        //        else
        //            result = ::DefWindowProc(GetHwnd(), nMsg, wParam, lParam);
        //    }
        //}
        return result;
    }
private:
    HWND hwnd;
    CefRefPtr<CefWindow> window;
};

//C:\wxWidgets-3.1.5\src\msw\window.cpp   2460行
