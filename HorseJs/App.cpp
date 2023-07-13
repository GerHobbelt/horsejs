#include "App.h"

namespace {
	static App* app;
}

App::App(const HINSTANCE& hInstance):hinstance{ hInstance }
{
	auto win = new Window(hInstance);
	windows.push_back(win);
	PageEnvironment::Init([&win]() {
		win->CreatePageController();
	});
}
App::~App()
{

}
void App::Init(const HINSTANCE& hInstance) {
	if (app) {
		return;
	}
	app = new App(hInstance);
}
App* App::Get() {
	return app;
}
void App::Dispose()
{
	delete app;
}