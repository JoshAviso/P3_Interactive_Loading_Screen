#pragma once

#include <Components/Renderers/ShapeRenderers/IShapeRenderer.h>

class PolygonRenderer : public IShapeRenderer
{
public:
	PolygonRenderer(uint8 sides, float radius) {
		_shape = new sf::CircleShape(radius, sides);
		_shape->setOrigin(radius, radius);
	}
	void SetRadius(float radius) {
		static_cast<sf::CircleShape*>(_shape)->setRadius(radius);
	}
	bool Intersects(Vec2 position) override { return false; }
};

