#pragma once

class Object;

class IComponent
{
protected:
	Object* _owner = nullptr;

public:
	virtual ~IComponent() = default;

	friend class Object;
};

