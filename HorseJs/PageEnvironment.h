#pragma once
#include <wrl.h>
#include <wil/com.h>
#include <memory>
#include "WebView2.h"
#include <functional>
class PageEnvironment
{
public:
	~PageEnvironment();
	static void Init(const std::function<void()> func);
	static PageEnvironment* Get();
	HRESULT callBack(HRESULT result, ICoreWebView2Environment* env);
	ICoreWebView2Environment* Environment;
private:
	std::function<void()> func;
};

