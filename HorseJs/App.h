#pragma once
#include "Window.h"
#include "PageEnvironment.h"
#include <memory>
#include <vector>
class App
{
public:
	~App();
	static void Init();
	static void Dispose();
	static App* Get();
private:
	App();
	std::vector<std::shared_ptr<Window>> windows;
};

