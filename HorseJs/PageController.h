#pragma once
#include "Page.h"

class PageController
{
public:
	PageController(ICoreWebView2Controller* ctrl);
	~PageController();
	ICoreWebView2Controller* Controller;
	Page* page;
private:


};

