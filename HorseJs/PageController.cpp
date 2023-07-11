#include "PageController.h"
#include "PageEnvironment.h"

using namespace Microsoft::WRL;
PageController::PageController(ICoreWebView2Controller* ctrl) :Controller{ctrl}
{
    wil::com_ptr<ICoreWebView2> webview;
    ctrl->get_CoreWebView2(&webview);
    page = std::make_shared<Page>(webview);
}
PageController::~PageController()
{

}
