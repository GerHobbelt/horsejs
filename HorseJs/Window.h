#pragma once
#include <Windows.h>
#include "PageController.h"
class Window
{
public:
	Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	static LRESULT CALLBACK RouteWindowMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT HitTest(HWND hwnd, POINT cursor);
	void CreatePageController();
	HWND hwnd;
	
private:
	void CreateWindowFrameless();
	HRESULT pageCtrlCallBack(HRESULT result, ICoreWebView2Controller* controller);
	std::vector<std::shared_ptr<PageController>> controllers;
};

