#pragma once

#include <Components/Renderers/ShapeRenderers/IShapeRenderer.h>

#include <Objects/Object.h>

class CircleRenderer : public IShapeRenderer
{
public:
	CircleRenderer(float radius){
		_shape = new sf::CircleShape(radius);
		_shape->setOrigin(radius, radius);
		_radius = radius;
	}
	void SetRadius(float radius) {
		static_cast<sf::CircleShape*>(_shape)->setRadius(radius);
		_radius = radius;
	}
	bool Intersects(Vec2 position) override {
		if (!_owner) return false;
		Vec2 dir = position - _owner->Position;
		return dir.sqrMagnitude() <= _radius * _radius;
	}

private:
	float _radius = 0.f;
};

