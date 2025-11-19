#pragma once

#include <Components/IComponent.h>

#include <SFML/Graphics.hpp>
#include <Math/Vec2.h>

class IRenderer : virtual public IComponent
{
public:
	int RenderLayer = 0;
	virtual ~IRenderer() = default;
	virtual bool Intersects(Vec2 position) = 0;

protected:
	virtual void Render(sf::RenderWindow& window) = 0;

	friend class ObjectManager;
};

