#include "PageController.h"

using namespace Microsoft::WRL;
PageController::PageController(HWND hwnd) :hwnd{hwnd}
{
	auto app = App::Get();
	auto callBackInstance = Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(this, &PageController::callBack);
	app->pageEnvironment->Environment->CreateCoreWebView2Controller(hwnd, callBackInstance.Get());
}
PageController::~PageController()
{

}
HRESULT PageController::callBack(HRESULT result, ICoreWebView2Controller* controller)
{
	this->Controller = controller;
	//��ʱ���Դ���Page��
	wil::com_ptr<ICoreWebView2> webview;
	controller->get_CoreWebView2(&webview);
	page = std::make_shared<Page>(webview);

	RECT bounds;
	GetClientRect(hwnd, &bounds);
	controller->put_Bounds(bounds);
	return S_OK;
}