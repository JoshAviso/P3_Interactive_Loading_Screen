#pragma once

#include <Components/Update/IUpdateComponent.h>
#include <Math/Vec2.h>

class ImagePanning : public IUpdateComponent
{
public:
	float _panX = 1.0f;
	float _panY = 1.0f;

public:
	ImagePanning(float panX, float panY);
	void Update(float deltaTime) override;

private:
	float elapsedTime = 0.0f;
	Vec2 origPos = {0,0};
	Object* nextBG;
	Object* nextChara;
};