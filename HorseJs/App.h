#pragma once
#include "PageEnvironment.h"
#include <memory>
#include <vector>
#include "Window.h"
class App
{
public:
	~App();
	static void Init();
	static void Dispose();
	static App* Get();
private:
	App();
	std::vector<Window *> windows;
};

