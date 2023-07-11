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
	static void Init(const std::function<void()>& func);
	static std::shared_ptr<PageEnvironment> Get();
	ICoreWebView2Environment* Environment;
private:
	std::function<void()> func;
	PageEnvironment();
	HRESULT callBack(HRESULT result, ICoreWebView2Environment* env);	
};

