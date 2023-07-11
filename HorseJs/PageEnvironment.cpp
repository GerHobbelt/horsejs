#include "PageEnvironment.h"
using namespace Microsoft::WRL;

namespace {
	static std::shared_ptr<PageEnvironment> pageEnv;
}

PageEnvironment::PageEnvironment()
{
	auto envCBInstance = Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(PageEnvironment::callBack);
	CreateCoreWebView2EnvironmentWithOptions(nullptr, nullptr, nullptr, envCBInstance.Get());
}
PageEnvironment::~PageEnvironment()
{

}

void PageEnvironment::Init(const std::function<void()>& func)
{
	if (pageEnv.get()) {
		return;
	}
	pageEnv = std::make_shared<PageEnvironment>();
	pageEnv->func = func;
}
std::shared_ptr<PageEnvironment> PageEnvironment::Get()
{

}

HRESULT PageEnvironment::callBack(HRESULT result, ICoreWebView2Environment* env)
{
	this->Environment = env;
	func();
	return S_OK;
}

//�ȴ���Env���ٴ���ԭ��Window��Env������֮��Window��Ȼ��������