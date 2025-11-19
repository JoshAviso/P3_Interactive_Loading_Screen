#pragma once

#include <Core/Color.h>
#include <Components/Renderers/IRenderer.h>

class IShapeRenderer : virtual public IRenderer
{
public:
	Color FillColor = Color::White();
	Color OutlineColor = Color::Black();
	float OutlineWidth = 0.0f;

protected:
	sf::Shape* _shape = nullptr;

public:
	void Render(sf::RenderWindow& window) override;
};

