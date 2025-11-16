#include "Application.h"

#include <Objects/ObjectManager.h>

void Application::Run()
{
    sf::Clock deltaClock;
    while (_window->isOpen()) {
        sf::Event event;
        while (_window->pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
				shouldClose = true;
            }
        }

        sf::Time deltaTime = deltaClock.restart();
        Update(deltaTime.asSeconds());
        Render();

		if (shouldClose)
			_window->close();
    }

}

void Application::Quit()
{
	shouldClose = true;
}

void Application::Update(float deltaTime)
{

}

void Application::Render()
{
    _window->clear();
	ObjectManager::_instance->RenderObjectsTo(*_window);

    _window->display();
}

// SINGLETON 
Application* Application::_instance = nullptr;
Application* Application::Initialize(const Desc& desc)
{
    if (_instance != nullptr) return _instance;

    _instance = new Application(desc);
    return _instance;
}

Application::Application(const Desc& desc)
{
    _appName = desc.appName;

    // Initialize Window
    _window = Make_Unique<sf::RenderWindow>(sf::VideoMode(desc.windowSize.w, desc.windowSize.h), desc.appName);
    
    // Manager Initializations
	ObjectManager::Initialize();
}

Application::~Application(){ }
