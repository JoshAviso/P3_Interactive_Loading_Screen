#include "Application.h"

#include <Core/Logger.h>
#include <Objects/ObjectManager.h>
#include <Resources/ResourceManager.h>

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
    ObjectManager::_instance->Update(deltaTime);
}

void Application::Render()
{
    _window->clear();
	ObjectManager::_instance->RenderObjectsTo(*_window);

    _window->display();
}

// SINGLETON 
Application* Application::Instance = nullptr;
Application* Application::Initialize(const Desc& desc)
{
    if (Instance != nullptr) return Instance;

    Instance = new Application(desc);
    return Instance;
}

Application::Application(const Desc& desc)
{
    _appName = desc.appName;
	_windowSize = desc.windowSize;

	Logger::Initialize(Logger::ELogLevel::Error);

    // Initialize Window
    _window = Make_Unique<sf::RenderWindow>(sf::VideoMode(desc.windowSize.w, desc.windowSize.h), desc.appName);
    
    // Manager Initializations
	ObjectManager::Initialize();
    ResourceManager::Initialize();
}

Application::~Application(){ }
