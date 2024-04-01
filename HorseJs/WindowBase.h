#pragma once
#include <Windows.h>
class WindowBase
{
public:
	WindowBase();
	WindowBase(const WindowBase&) = delete;
	WindowBase& operator=(const WindowBase&) = delete;
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT HitTest(HWND hwnd, POINT cursor);
	HWND hWnd;
private:
	void CreateWindowFrameless();
};

