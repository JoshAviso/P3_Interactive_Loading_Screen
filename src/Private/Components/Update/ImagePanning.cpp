#include <Components/Update/ImagePanning.h>

#include <Objects/Object.h>
#include <Core/Logger.h>
#include <Objects/ObjectManager.h>
#include <Math/Vec2.h>

ImagePanning::ImagePanning(float panX, float panY)
{
	_panX = panX;
	_panY = panY;
}

void ImagePanning::Update(float deltaTime)
{
	//Get original position to reset to, putting it in constructor no worky
	if (origPos.x == 0 && origPos.y == 0)
		origPos = _owner->Position;

	elapsedTime += deltaTime;

	//Pan
	if(elapsedTime < 3.0f)
		_owner->Position += {_panX, _panY};

	else if (_owner->Name == "BG1" && elapsedTime > 3.0f)
	{
		nextBG = ObjectManager::FindObjectByName("BG2");
		
		nextBG->Enabled = true;

		elapsedTime = 0;
		_owner->Position = origPos;
		_owner->Enabled = false;
	}

	else if (_owner->Name == "BG2" && elapsedTime > 3.0f)
	{
		nextBG = ObjectManager::FindObjectByName("BG1");

		nextBG->Enabled = true;

		elapsedTime = 0;
		_owner->Position = origPos;
		_owner->Enabled = false;
	}

	else if (_owner->Name == "CHARA1" && elapsedTime > 3.0f)
	{
		nextChara = ObjectManager::FindObjectByName("CHARA2");

		nextChara->Enabled = true;

		elapsedTime = 0;
		_owner->Position = origPos;
		_owner->Enabled = false;
	}

	else if (_owner->Name == "CHARA2" && elapsedTime > 3.0f)
	{
		nextChara = ObjectManager::FindObjectByName("CHARA1");

		nextChara->Enabled = true;

		elapsedTime = 0;
		_owner->Position = origPos;
		_owner->Enabled = false;
	}
}