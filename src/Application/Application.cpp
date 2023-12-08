#include "Application/Application.hpp"

Application::Application()
{
}

Application::~Application()
{
}

void Application::onCreate()
{
	Game::onCreate();
	auto e = this->getEntitySystem()->createEntity<Entity>();
}
