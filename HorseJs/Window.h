#pragma once
#include <Windows.h>
class Window
{
public:
	Window();
	Window(const WindowBase&) = delete;
	Window& operator=(const WindowBase&) = delete;
	static LRESULT CALLBACK RouteWindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT HitTest(HWND hwnd, POINT cursor);
	HWND hWnd;
	
private:
	void CreateWindowFrameless();
};

