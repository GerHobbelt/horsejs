#include "App.h"

namespace {
	static App* app;
}

App::App()
{
	auto win = new Window();
	windows.push_back(win);
	PageEnvironment::Init([&win]() {
		win->CreatePageController();
	});
}
App::~App()
{

}
void App::Init() {
	if (app) {
		return;
	}
	app = new App();
}
App* App::Get() {
	return app;
}
void App::Dispose()
{
	delete app;
}