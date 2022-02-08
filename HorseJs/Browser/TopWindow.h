#pragma once
#include <wx/wx.h>

class TopWindow : public wxFrame
{
public:
    TopWindow() : wxFrame(NULL, wxID_ANY, "Hello World") {};
};

