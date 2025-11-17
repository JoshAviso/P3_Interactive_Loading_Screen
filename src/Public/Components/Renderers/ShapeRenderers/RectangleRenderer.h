#pragma once

#include <Components/Renderers/ShapeRenderers/IShapeRenderer.h>

class RectangleRenderer : public IShapeRenderer
{
public:
	RectangleRenderer(Vec2 size) {
		_shape = new sf::RectangleShape(sf::Vector2f(size.x, size.y));
		_shape->setOrigin(size.x / 2.f, size.y / 2.f);
	}
	void SetSize(Vec2 size) {
		static_cast<sf::RectangleShape*>(_shape)->setSize(sf::Vector2f(size.x, size.y));
	}
};

