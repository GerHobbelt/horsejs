#pragma once
#include <Windows.h>
#include <vector>
#include "PageController.h"
#include <memory>
#include <wrl.h>
#include <wil/com.h>
#include "WebView2.h"

class Window
{
public:
	Window();
	static LRESULT CALLBACK RouteWindowMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT HitTest(HWND hwnd, POINT cursor);
	void CreatePageController();
	HWND hwnd;	
private:
	void CreateWindowFrameless();
	HRESULT pageCtrlCallBack(HRESULT result, ICoreWebView2Controller* controller);
	std::vector<PageController*> controllers;
};

