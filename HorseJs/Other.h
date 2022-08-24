#pragma once
#include "include/cef_app.h"
class Other :public CefApp
{
public:
	Other() = default;
	Other(const Other&) = delete;
	Other& operator=(const Other&) = delete;
private:
	IMPLEMENT_REFCOUNTING(Other);
};
