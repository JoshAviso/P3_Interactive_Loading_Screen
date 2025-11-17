#pragma once

#include <Components/Renderers/ShapeRenderers/IShapeRenderer.h>

class TriangleRenderer : public IShapeRenderer
{
public:
	TriangleRenderer(float radius) {
		_shape = new sf::CircleShape(radius, 3);
		_shape->setOrigin(radius, radius);
	}
	void SetRadius(float radius) {
		static_cast<sf::CircleShape*>(_shape)->setRadius(radius);
	}
};

