#pragma once

#include <Components/Renderers/ShapeRenderers/IShapeRenderer.h>

#include <Math/Constants.h>

class RectangleRenderer : public IShapeRenderer
{
public:
	RectangleRenderer(Vec2 size) {
		_shape = new sf::RectangleShape(sf::Vector2f(size.x, size.y));
		_shape->setOrigin(size.x / 2.f, size.y / 2.f);
		_size = size;
	}
	void SetSize(Vec2 size) {
		static_cast<sf::RectangleShape*>(_shape)->setSize(sf::Vector2f(size.x, size.y));
		_size = size;
	}
	bool Intersects(Vec2 position) override {
		if (!_owner) return false;
		if (!_owner->Enabled) return false;

		float rotRad = _owner->Rotation * fPI / 180.f;
		Vec2 dPos = position - _owner->Position;
		Vec2 locPos = {
			dPos.x * std::cos(-rotRad) - dPos.y * std::sin(-rotRad),
			dPos.x * std::sin(-rotRad) + dPos.y * std::cos(-rotRad)
		};

		Vec2 halfSize = _size / 2.f;
		return
			-halfSize.x <= locPos.x && locPos.x <= halfSize.x &&
			-halfSize.y <= locPos.y && locPos.y <= halfSize.y;
	}

private:
	Vec2 _size = { 0.f, 0.f };
};

