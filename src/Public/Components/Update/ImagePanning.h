#pragma once

#include <Components/Update/IUpdateComponent.h>

class ImagePanning : public IUpdateComponent
{
public:
	float _panX = 1.0f;
	float _panY = 1.0f;
	float elapsedTime = 0.0f;

public:
	ImagePanning(float panX, float panY);
	void Update(float deltaTime) override;
};