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
	};

	void Run();
	void Quit();

private:
	String _appName = "";
	Unique<sf::RenderWindow> _window = nullptr;
	bool shouldClose = false;

	void Update(float deltaTime);
	void Render();

// SINGLETON
public:
	static Application* Initialize(const Desc& desc);
private:
	static Application* _instance;
	explicit Application(const Desc& desc);
	~Application();
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
};

