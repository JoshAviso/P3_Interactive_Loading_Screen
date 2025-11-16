#pragma once

#include <Objects/Shapes/IShape.h>

class CircleShape : public IShape
{
public:
	CircleShape(float radius) {
		_shape = new sf::CircleShape(radius);
	}
	void SetRadius(float radius) {
		static_cast<sf::CircleShape*>(_shape)->setRadius(radius);
	}
};

