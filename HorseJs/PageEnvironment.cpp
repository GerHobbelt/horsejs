#include "PageEnvironment.h"
#include <iostream>
using namespace Microsoft::WRL;

namespace {
	static PageEnvironment* pageEnv;
}

PageEnvironment::~PageEnvironment()
{

}
void PageEnvironment::Init(const std::function<void()> func)
{
	if (pageEnv) {
		return;
	}
	pageEnv = new PageEnvironment();
	pageEnv->func = func;
	//auto envCBInstance = Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(pageEnv, &PageEnvironment::callBack);
	//HRESULT result = CreateCoreWebView2EnvironmentWithOptions(nullptr, nullptr, nullptr, envCBInstance.Get());



	std::wstring m_userDataFolder = L"C:\\MyAppUserDataFolder";
	HRESULT hr = CreateCoreWebView2EnvironmentWithOptions(
		NULL, m_userDataFolder.c_str(), nullptr,
		Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(pageEnv, &PageEnvironment::callBack).Get());
}
PageEnvironment* PageEnvironment::Get()
{
	return pageEnv;
}

HRESULT PageEnvironment::callBack(HRESULT result, ICoreWebView2Environment* env)
{
	this->Environment = env;
	func();
	return S_OK;
}

//先创建Env，再创建原生Window，Env创建好之后，Window必然创建好了