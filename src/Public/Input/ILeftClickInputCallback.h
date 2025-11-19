#pragma once

#include <Math/Vec2i.h>
#include <Input/Input.h>

class ILeftClickInputCallback
{
public:
	ILeftClickInputCallback() { Input::RegisterLeftClickCallback(this); }
	virtual ~ILeftClickInputCallback() { Input::UnregisterLeftClickCallback(this); }

protected:
	virtual void OnLeftClickPressed(Vec2i mousePosition) {};
	virtual void OnLeftClickReleased(Vec2i mousePosition) {};
	friend class Input;
};

