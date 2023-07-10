#include "WindowNative.h"


namespace {
	// Pointer to WebViewController
	static wil::com_ptr<ICoreWebView2Controller> webviewController;
	// Pointer to WebView window
	static wil::com_ptr<ICoreWebView2> webview;
    static void Log(std::string& str) {
        OutputDebugStringA(str.c_str());
        OutputDebugStringA("\r\n");
    }
}
using namespace Microsoft::WRL;
WindowNative::WindowNative() {
	auto envCB = [this](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {

		auto ctrlCBInstance = Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(this,&WindowNative::CreateBrowserView);
		//2
		env->CreateCoreWebView2Controller(hWnd, ctrlCBInstance.Get());
		return S_OK;
	};
	auto envCBInstance = Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(envCB);
	//1
	CreateCoreWebView2EnvironmentWithOptions(nullptr, nullptr, nullptr, envCBInstance.Get());
}

HRESULT WindowNative::CreateBrowserView(HRESULT result, ICoreWebView2Controller* controller) {
	//3
	if (controller != nullptr) {
		webviewController = controller;
		webviewController->get_CoreWebView2(&webview);
	}
	ConfigWebView();
	// <NavigationEvents>
	// Step 4 - Navigation events
	// register an ICoreWebView2NavigationStartingEventHandler to cancel any non-https navigation
	EventRegistrationToken token;
	auto navigateCB = Callback<ICoreWebView2NavigationStartingEventHandler>(this, &WindowNative::NavigationStarting);
	webview->add_NavigationStarting(navigateCB.Get(), &token);
	// </NavigationEvents>
	// <Scripting>
	// Step 5 - Scripting
	// Schedule an async task to add initialization script that freezes the Object object
	webview->AddScriptToExecuteOnDocumentCreated(L"Object.freeze(Object);", nullptr);
	// Schedule an async task to get the document URL
	webview->ExecuteScript(L"window.document.URL;", Callback<ICoreWebView2ExecuteScriptCompletedHandler>(
		[](HRESULT errorCode, LPCWSTR resultObjectAsJson) -> HRESULT {
			LPCWSTR URL = resultObjectAsJson;
	//doSomethingWithURL(URL);
	return S_OK;
		}).Get());
	// </Scripting>

	// Step 6 - Communication between host and web content
	// Set an event handler for the host to return received message back to the web content
	webview->add_WebMessageReceived(Callback<ICoreWebView2WebMessageReceivedEventHandler>(
		[](ICoreWebView2* webview, ICoreWebView2WebMessageReceivedEventArgs* args) -> HRESULT {
			wil::unique_cotaskmem_string message;
	args->TryGetWebMessageAsString(&message);
	// processMessage(&message);
	webview->PostWebMessageAsString(message.get());
	return S_OK;
		}).Get(), &token);
	// Schedule an async task to add initialization script that
	// 1) Add an listener to print message from the host
	// 2) Post document URL to the host
	//webview->AddScriptToExecuteOnDocumentCreated(
	//	L"window.chrome.webview.addEventListener(\'message\', event => alert(event.data));" \
	//	L"window.chrome.webview.postMessage(window.document.URL);",
	//	nullptr);
	//webview->OpenDevToolsWindow();
	return S_OK;
}

HRESULT WindowNative::NavigationStarting(ICoreWebView2* webview, ICoreWebView2NavigationStartingEventArgs* args){
	wil::unique_cotaskmem_string uri;
	args->get_Uri(&uri);
	std::wstring source(uri.get());
	if (source.substr(0, 5) != L"https") {
		args->put_Cancel(true);
	}
	return S_OK;
}
void WindowNative::ConfigWebView() {
	// Add a few settings for the webview
	// The demo step is redundant since the values are the default settings
	wil::com_ptr<ICoreWebView2Settings> settings;
	webview->get_Settings(&settings);
	settings->put_IsScriptEnabled(TRUE);
	settings->put_AreDefaultScriptDialogsEnabled(TRUE);
	settings->put_IsWebMessageEnabled(TRUE);
	// Resize WebView to fit the bounds of the parent window
	RECT bounds;
	GetClientRect(hWnd, &bounds);
	webviewController->put_Bounds(bounds);
	// Schedule an async task to navigate to Bing
	webview->Navigate(L"https://www.baidu.com/");
}