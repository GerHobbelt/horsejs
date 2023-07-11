#include "App.h"

namespace {
	static std::shared_ptr<App> app;
}

App::App()
{
	auto win = std::make_shared<Window>();
	windows.push_back(win);
	PageEnvironment::Init([&win]() {
		win->CreatePageController();
	});
}
App::~App()
{

}
void App::Init() {
	if (app.get()) {
		return;
	}
	app = std::make_unique<App>();
}
std::shared_ptr<App> App::Get() {
	return app;
}