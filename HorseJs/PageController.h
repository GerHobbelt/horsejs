#pragma once
#include "App.h"
#include "Page.h"

class PageController
{
public:
	PageController(ICoreWebView2Controller* ctrl);
	~PageController();
	ICoreWebView2Controller* Controller;
	std::shared_ptr<Page> page;
private:
};

