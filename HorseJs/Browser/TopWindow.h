#pragma once
#include <wx/wx.h>

class TopWindow : public wxFrame
{
public:
    TopWindow() : wxFrame(NULL, wxID_ANY, "") {
        Bind(wxEVT_CLOSE_WINDOW, &TopWindow::OnClose,this);
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
        //this->Close(true); //会循环调用此事件
        this->Destroy();
        //Destroy();
    };
    ~TopWindow() {

    }
};

