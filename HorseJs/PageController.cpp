#include "PageController.h"
#include "App.h"
#include "PageEnvironment.h"

using namespace Microsoft::WRL;
PageController::PageController(ICoreWebView2Controller* ctrl) :Controller{ctrl}
{
    page = new Page();
    auto result = ctrl->get_CoreWebView2(&page->webview);
    page->Init();
}
PageController::~PageController()
{

}
