#include <Objects/Shapes/IShape.h>

#include <Core/Logger.h>

void IShape::DrawTo(sf::RenderWindow& window)
{
	_shape->setPosition(Position.x, Position.y);
	_shape->setFillColor((sf::Color)FillColor);
	_shape->setOutlineColor((sf::Color)OutlineColor);
	_shape->setOutlineThickness(OutlineWidth);

	window.draw(*_shape);
	Logger::Log("Drawing Shape: " + Name);
}
