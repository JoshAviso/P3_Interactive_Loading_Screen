#pragma once

#include <Objects/Shapes/IShape.h>

class RectangleShape : public IShape
{
public:
	RectangleShape(Vec2 size) {
		_shape = new sf::RectangleShape(sf::Vector2f(size.x, size.y));
	}
	void SetSize(Vec2 size) {
		static_cast<sf::RectangleShape*>(_shape)->setSize(sf::Vector2f(size.x, size.y));
	}
};

