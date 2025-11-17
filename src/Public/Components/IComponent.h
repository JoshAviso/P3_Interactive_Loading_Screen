#pragma once

class IComponent
{
public:
	virtual ~IComponent() = default;
	virtual void Update(float deltaTime) = 0;
};

