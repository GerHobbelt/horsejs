#include "App.h"

namespace {
	std::shared_ptr<App> app;
}

App::App()
{
	pageEnvironment = std::make_unique<PageEnvironment>();
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