#pragma once

#include <Core/Common.h>
#include <Core/String.h>
#include <SFML/Graphics.hpp>
#include <Math/Vec2i.h>

class Application
{
public:
	struct Desc {
		String appName;
		Vec2i windowSize;
		int fpsCap;
	};

	void Run();
	void Quit();

public:
	static Vec2i WindowSize() { return Instance->_windowSize; }
	sf::RenderWindow* GetWindow() const { return _window.get(); };

private:
	String _appName = "";
	Vec2i _windowSize;
	Unique<sf::RenderWindow> _window = nullptr;
	bool shouldClose = false;

	void Update(float deltaTime);
	void Render();

// SINGLETON
public:
	static Application* Initialize(const Desc& desc);
	static Application* Instance;
private:
	explicit Application(const Desc& desc);
	~Application();
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
};

