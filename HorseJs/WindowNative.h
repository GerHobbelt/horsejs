#pragma once
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <wrl.h>
#include <wil/com.h>
#include "WebView2.h"
#include "WindowBase.h"
class WindowNative:public WindowBase
{
public:
	WindowNative();
	WindowNative(const WindowNative&) = delete;
	WindowNative& operator=(const WindowNative&) = delete;	
private:
	HRESULT CreateBrowserView(HRESULT result, ICoreWebView2Controller* controller);
	HRESULT NavigationStarting(ICoreWebView2* webview, ICoreWebView2NavigationStartingEventArgs* args);
	void ConfigWebView();
};

