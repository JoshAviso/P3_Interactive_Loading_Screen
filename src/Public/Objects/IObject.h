#pragma once

#include <Core/String.h>
#include <Math/Vec2.h>

#include <SFML/Graphics.hpp>

class IObject
{
public:
	String Name;
	Vec2 Position;

public:
	virtual ~IObject() = default;
	virtual void DrawTo(sf::RenderWindow& window) = 0;
};

