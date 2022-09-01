#pragma once
#include "include/views/cef_label_button.h"
class ButtonDelegate : public CefButtonDelegate
{
public:
    ButtonDelegate() = default;
    void OnButtonPressed(CefRefPtr<CefButton> button) override {
        auto a = button->GetID();
    };
private:
    IMPLEMENT_REFCOUNTING(ButtonDelegate);
    DISALLOW_COPY_AND_ASSIGN(ButtonDelegate);
};