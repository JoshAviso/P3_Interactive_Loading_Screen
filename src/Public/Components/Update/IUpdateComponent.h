#pragma once

#include <Components/IComponent.h>

class IUpdateComponent : public IComponent
{
public:
	virtual ~IUpdateComponent() = default;
	virtual void Update(float deltaTime) = 0;
};

