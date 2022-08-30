#pragma once

#include "include/cef_app.h"
class OtherProcessHandler :public CefApp
{
public:
	OtherProcessHandler() = default;
	OtherProcessHandler(const OtherProcessHandler&) = delete;
	OtherProcessHandler& operator=(const OtherProcessHandler&) = delete;
private:
	IMPLEMENT_REFCOUNTING(OtherProcessHandler);
};

