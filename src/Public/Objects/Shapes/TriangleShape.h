#pragma once

#include <Objects/Shapes/IShape.h>

class TriangleShape : public IShape
{
public:
	TriangleShape(float radius) : IShape("Triangle") {
		_shape = new sf::CircleShape(radius, 3);
		_shape->setOrigin(radius, radius);
	}
	void SetRadius(float radius) {
		static_cast<sf::CircleShape*>(_shape)->setRadius(radius);
	}
};

