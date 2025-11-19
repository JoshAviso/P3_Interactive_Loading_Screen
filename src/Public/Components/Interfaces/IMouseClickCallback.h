#pragma once
#include <Components/IComponent.h>
#include <Input/ILeftClickInputCallback.h>
#include <Math/Vec2i.h>
#include <Objects/Object.h>

class IMouseClickCallback : virtual public IComponent, public ILeftClickInputCallback {

protected:
	virtual void OnClickedOnCallback(Vec2i mousePosition) {};
	virtual void OnReleasedOnCallback(Vec2i mousePosition) {};

private:
	virtual void OnLeftClickPressed(Vec2i mousePosition) override {
		if (_owner && _owner->Intersects({ (float)mousePosition.x, (float)mousePosition.y })) OnClickedOnCallback(mousePosition); };
	virtual void OnLeftClickReleased(Vec2i mousePosition) override {
		if (_owner && _owner->Intersects({ (float)mousePosition.x, (float)mousePosition.y })) OnReleasedOnCallback(mousePosition); };

	friend class Input;
};