#include "PageEnvironment.h"

using namespace Microsoft::WRL;

PageEnvironment::PageEnvironment()
{
	auto envCBInstance = Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(PageEnvironment::callBack);
	CreateCoreWebView2EnvironmentWithOptions(nullptr, nullptr, nullptr, envCBInstance.Get());
}
PageEnvironment::~PageEnvironment()
{

}

HRESULT PageEnvironment::callBack(HRESULT result, ICoreWebView2Environment* env)
{
	return S_OK;
}

//�ȴ���Env���ٴ���ԭ��Window��Env������֮��Window��Ȼ��������