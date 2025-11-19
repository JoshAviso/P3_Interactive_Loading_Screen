#include <Components/Renderers/ShapeRenderers/IShapeRenderer.h>

#include <Core/Logger.h>
#include <Objects/Object.h>

void IShapeRenderer::Render(sf::RenderWindow& window)
{
	_shape->setPosition(_owner->Position.x, _owner->Position.y);
	_shape->setRotation(_owner->Rotation);
	_shape->setScale(_owner->Scale.x, _owner->Scale.y);

	_shape->setFillColor((sf::Color)FillColor);
	_shape->setOutlineColor((sf::Color)OutlineColor);
	_shape->setOutlineThickness(OutlineWidth);

	window.draw(*_shape);
}
