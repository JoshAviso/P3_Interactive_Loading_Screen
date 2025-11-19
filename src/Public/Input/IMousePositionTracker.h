#pragma once
#include <Math/Vec2.h>
#include <Input/Input.h>

class IMousePositionTracker
{
public:
	IMousePositionTracker() { Input::RegisterMousePositionTracker(this); }
	virtual ~IMousePositionTracker() { Input::UnregisterMousePositionTracker(this); }

protected:
	virtual void CheckPosition(Vec2i mousePosition) {};

	friend class Input;
};

