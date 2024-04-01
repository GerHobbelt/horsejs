#pragma once
#include <wrl.h>
#include <wil/com.h>
#include "WebView2.h"
#include <iostream>
class Page
{
public:
	Page(wil::com_ptr<ICoreWebView2>&& webview);
	~Page();
	void Navigate(const std::string& url);
	void ExecuteScript();
	void OpenDevTools();
	wil::com_ptr<ICoreWebView2> webview;
private:
	HRESULT navigationStarting(ICoreWebView2* webview, ICoreWebView2NavigationStartingEventArgs* args);
	HRESULT messageReceived(ICoreWebView2* webview, ICoreWebView2WebMessageReceivedEventArgs* args);
};

