#include "Page.h"

Page::Page(wil::com_ptr<ICoreWebView2> webview):webview{ webview }
{
	wil::com_ptr<ICoreWebView2Settings> settings;
	webview->get_Settings(&settings);
	settings->put_IsScriptEnabled(TRUE);
	settings->put_AreDefaultScriptDialogsEnabled(TRUE);
	settings->put_IsWebMessageEnabled(TRUE);
	// Schedule an async task to navigate to Bing
	webview->Navigate(L"https://www.baidu.com/");
}
Page::~Page()
{

}