#pragma once
#include "PageEnvironment.h"
#include <memory>
#include <vector>
#include "Window.h"
class App
{
public:
	~App();
	static void Init(const HINSTANCE& hInstance);
	static void Dispose();
	static App* Get();
	HINSTANCE hinstance;
private:
	App(const HINSTANCE& hInstance);
	std::vector<Window*> windows;
};

