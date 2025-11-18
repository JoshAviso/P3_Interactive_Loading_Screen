#include <Components/Update/ImagePanning.h>

#include <Objects/Object.h>
#include <Core/Logger.h>

ImagePanning::ImagePanning(float panX, float panY)
{
	_panX = panX;
	_panY = panY;
}

void ImagePanning::Update(float deltaTime)
{
	elapsedTime += deltaTime;

	_owner->Position += {_panX, _panY};

	//if (elapsedTime > 5.0f) _owner->Enabled = false;

	//if(!_owner->Enabled) Logger::Log("test");
}