#pragma once
#include "wx/nativewin.h"
#include "TopWindow.h"
#include <wx/timer.h>
#include "wx/msw/private.h"
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
    }
    virtual ~NativeWindow()
    {
        Disown();
    }
private:
    wxWindow* parent;
};
