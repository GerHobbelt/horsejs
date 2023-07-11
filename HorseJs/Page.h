#pragma once
#include <wrl.h>
#include <wil/com.h>
#include "WebView2.h"
class Page
{
public:
	Page(wil::com_ptr<ICoreWebView2> webview);
	~Page();
private:
	wil::com_ptr<ICoreWebView2> webview;
};

