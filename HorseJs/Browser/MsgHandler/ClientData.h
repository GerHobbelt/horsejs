#pragma once
#include "include/cef_app.h"
#include <wx/clntdata.h>


class ClientData : public wxClientData,public wxObject
{
public:
	ClientData() = default;
	CefRefPtr<CefFrame> frame;
	std::string msgName;
	bool isUsed = false;
};