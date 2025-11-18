#pragma once

#include <Components/IComponent.h>

#include <SFML/Graphics.hpp>

class IRenderer : public IComponent
{
public:
	int RenderLayer = 0;
	virtual ~IRenderer() = default;

protected:
	virtual void Render(sf::RenderWindow& window) = 0;

	friend class ObjectManager;
};

