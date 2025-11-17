#pragma once

#include <Objects/Shapes/IShape.h>

class PolygonShape : public IShape
{
public:
	PolygonShape(String name, uint8 sides, float radius) : IShape(name) {
		_shape = new sf::CircleShape(radius, sides);
		_shape->setOrigin(radius, radius);
	}
	void SetRadius(float radius) {
		static_cast<sf::CircleShape*>(_shape)->setRadius(radius);
	}
};

