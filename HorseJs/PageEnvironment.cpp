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

//先创建Env，再创建原生Window，Env创建好之后，Window必然创建好了