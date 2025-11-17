#pragma once

#include <Objects/IObject.h>
#include <Core/Color.h>

class IShape : public IObject
{
public:
	Color FillColor = Color::White();
	Color OutlineColor = Color::Black();
	float OutlineWidth = 0.0f;

protected:
	sf::Shape* _shape = nullptr;

public:
	IShape(String name) : IObject(name) {}
	void DrawTo(sf::RenderWindow& window) override;
};

