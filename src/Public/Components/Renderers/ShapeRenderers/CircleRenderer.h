#pragma once

#include <Components/Renderers/ShapeRenderers/IShapeRenderer.h>

class CircleRenderer : public IShapeRenderer
{
public:
	CircleRenderer(float radius) {
		_shape = new sf::CircleShape(radius);
		_shape->setOrigin(radius, radius);
	}
	void SetRadius(float radius) {
		static_cast<sf::CircleShape*>(_shape)->setRadius(radius);
	}
	bool Intersects(Vec2 position) override { return false; }
};

