#pragma once
#include "Window.h"
#include "PageEnvironment.h"
#include <memory>
class App
{
public:
	~App();
	static void Init();
	static std::shared_ptr<App> Get();
	std::unique_ptr<PageEnvironment> pageEnvironment;
private:
	App();
};

