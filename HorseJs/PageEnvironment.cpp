#include "PageEnvironment.h"
using namespace Microsoft::WRL;

namespace {
	static PageEnvironment* pageEnv;
}

PageEnvironment::PageEnvironment()
{
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
	auto envCBInstance = Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(pageEnv, &PageEnvironment::callBack);
	CreateCoreWebView2EnvironmentWithOptions(nullptr, nullptr, nullptr, envCBInstance.Get());
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