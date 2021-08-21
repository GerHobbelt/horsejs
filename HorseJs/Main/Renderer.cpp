#include "Renderer.h"
#include <iostream>
//#include "HorseV8Handler.h"
void Renderer::OnWebKitInitialized()
{
    std::string extensionCode =
        "var test;"
        "if (!test)"
        "  test = {};"
        "(function() {"
        "  test.myval = 'My Value!';"
        "  test.myfunc = function() {"
        "    native function myfunc();"
        "    return myfunc();"
        "  };"
        "})();";

    // Create an instance of my CefV8Handler object.
    //CefRefPtr<CefV8Handler> handler = new HorseV8Handler();

    // Register the extension.
    //CefRegisterExtension("v8/test", extensionCode, handler);
}
void Renderer::OnBrowserDestroyed(CefRefPtr<CefBrowser> browser)
{
    std::cout << "allen";
}
void Renderer::OnFocusedNodeChanged(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefDOMNode> node)
{
    std::cout << "allen";
}
