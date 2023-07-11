#pragma once
#include <wrl.h>
#include <wil/com.h>
#include "WebView2.h"
class PageEnvironment
{
public:
	PageEnvironment();
	~PageEnvironment();
	ICoreWebView2Environment* Environment;
private:
	HRESULT callBack(HRESULT result, ICoreWebView2Environment* env);	
};

