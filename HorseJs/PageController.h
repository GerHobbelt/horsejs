#pragma once
#include "App.h"
#include "Page.h"

class PageController
{
public:
	PageController(HWND hwnd);
	~PageController();
	ICoreWebView2Controller* Controller;
	std::shared_ptr<Page> page;
private:
	HRESULT callBack(HRESULT result, ICoreWebView2Controller* controller);
	HWND hwnd;
};

