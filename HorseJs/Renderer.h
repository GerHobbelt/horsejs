#pragma once
#include "include/cef_app.h"
#include "V8Handler.h"
class Renderer :public CefApp, public CefRenderProcessHandler
{
public:
	Renderer() = default;
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override { return this; }
	void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) override;
	
private:
	IMPLEMENT_REFCOUNTING(Renderer);
	CefRefPtr<V8Handler> v8Handler;
};
