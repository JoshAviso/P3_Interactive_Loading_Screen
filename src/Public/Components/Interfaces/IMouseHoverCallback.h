#pragma once
#include <Components/IComponent.h>
#include <Input/IMousePositionTracker.h>
#include <Math/Vec2i.h>
#include <Objects/Object.h>

class IMouseHoverCallback : virtual public IComponent, public IMousePositionTracker {

protected:
	virtual void OnHoveredOnCallback(Vec2i mousePosition) {};
	virtual void OnHoveredOffCallback(Vec2i mousePosition) {};

private:
	bool _wasHoveringOn = false;
	void CheckPosition(Vec2i mousePosition) override {
		if (_owner && _owner->Intersects({ (float)mousePosition.x, (float)mousePosition.y })) {
			if (!_wasHoveringOn) {
				_wasHoveringOn = true;
				OnHoveredOnCallback(mousePosition);
			}
		}
		else if (_wasHoveringOn) {
			_wasHoveringOn = false;
			OnHoveredOffCallback(mousePosition);
		}
	}
	friend class Input;
};