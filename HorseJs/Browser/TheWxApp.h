#pragma once
#include <wx/wx.h>
class TheWxApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        return true;
    }
};
