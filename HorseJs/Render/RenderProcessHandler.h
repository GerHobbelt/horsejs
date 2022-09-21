#pragma once
#include "include/cef_app.h"
#include "V8Handler.h"
class RenderProcessHandler :public CefApp, public CefRenderProcessHandler
{
public:
	RenderProcessHandler() = default;
	RenderProcessHandler(const RenderProcessHandler&) = delete;
	RenderProcessHandler& operator=(const RenderProcessHandler&) = delete;
	CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override { return this; }
	bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) override;
	void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) override;
	void OnBrowserCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDictionaryValue> extraInfo) override;

private:
	IMPLEMENT_REFCOUNTING(RenderProcessHandler);
	CefRefPtr<V8Handler> v8Handler;
	int winId;
	int curViewId;
	int mainViewId;
};

