#include "PageController.h"
#include "App.h"
#include "PageEnvironment.h"
using namespace Microsoft::WRL;
static wil::com_ptr<ICoreWebView2> webview;


PageController::PageController(ICoreWebView2Controller* ctrl) : Controller{ctrl}
{
    page = new Page();
    auto result = Controller->get_CoreWebView2(&page->webview);
    page->Init();


    //Controller->get_CoreWebView2(&webview);
    //wil::com_ptr<ICoreWebView2Settings> settings;
    //webview->get_Settings(&settings);
    //settings->put_IsScriptEnabled(TRUE);
    //settings->put_AreDefaultScriptDialogsEnabled(TRUE);
    //settings->put_IsWebMessageEnabled(TRUE);    //
    //webview->Navigate(L"https://www.bing.com/");

}
PageController::~PageController()
{

}
