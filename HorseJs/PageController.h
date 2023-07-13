#pragma once
#include "Page.h"

class PageController
{
public:
	PageController(ICoreWebView2Controller* ctrl);
	~PageController();
	wil::com_ptr<ICoreWebView2Controller> Controller;
	Page* page;
private:


};

