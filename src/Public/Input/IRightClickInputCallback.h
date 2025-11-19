#pragma once
#include <Math/Vec2.h>
#include <Input/Input.h>

class IRightClickInputCallback
{
public:
	IRightClickInputCallback() { Input::RegisterRightClickCallback(this); }
	virtual ~IRightClickInputCallback() { Input::UnregisterRightClickCallback(this); }

protected:
	virtual void OnRightClickPressed(Vec2i mousePosition) {};
	virtual void OnRightClickReleased(Vec2i mousePosition) {};
	friend class Input;
};

