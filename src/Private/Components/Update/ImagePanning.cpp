#include <Components/Update/ImagePanning.h>

#include <Objects/Object.h>
#include <Core/Logger.h>
#include <Objects/ObjectManager.h>
#include <Math/Vec2.h>

#include <algorithm>

#include <Components/Renderers/SpriteRenderer.h>

ImagePanning::ImagePanning(float panTime, float fadeTime, List<ObjectPanningInfo>& objects) 
	: _panTime(panTime), _fadeTime(fadeTime)
{
	std::stable_sort(objects.begin(), objects.end(),
		[](const ObjectPanningInfo& a, const ObjectPanningInfo& b) {
		return a.setNumber < b.setNumber;
	});

	for (int i = 0; i < objects.size(); i++)
	{
		if (_objects.find(objects[i].setNumber) == _objects.end())
		{
			_objects[objects[i].setNumber] = List<ObjectPanningInfo>{};
		}

		_objects[objects[i].setNumber].push_back(objects[i]);

		ToggleObject(objects[i], false);
	}

	setCount = _objects.size();

	_currentObjects = &_objects[0];
	for (int i = 0; i < _currentObjects->size(); i++) {
		ToggleObject((*_currentObjects)[i], true);
	}
}

void ImagePanning::Update(float deltaTime)
{
	//OldUpdate(deltaTime);

	elapsedTime += deltaTime;

	if (elapsedTime <= _fadeTime) {
		// Still transitioning the current and prev sets


		// Panning and fading in the current set
		for (int i = 0; i < _currentObjects->size(); i++) {
			(*_currentObjects)[i].object->Position += (*_currentObjects)[i].panSpeed * deltaTime;
			SpriteRenderer* sr = (*_currentObjects)[i].object->GetComponent<SpriteRenderer>();
			if(sr) sr->Color.a += ((*_currentObjects)[i].maxAlpha / _fadeTime) * deltaTime;
		}

		// Panning and fading out the previous set
		if (_prevObjects != nullptr) {
			for (int i = 0; i < _prevObjects->size(); i++) {
				(*_prevObjects)[i].object->Position += (*_prevObjects)[i].panSpeed * deltaTime;
				SpriteRenderer* sr = (*_prevObjects)[i].object->GetComponent<SpriteRenderer>();
				if(sr) sr->Color.a -= ((*_prevObjects)[i].maxAlpha / _fadeTime) * deltaTime;
			}
		}
	}
	else if (elapsedTime <= _panTime + _fadeTime) {
		// Disable previous set
		if (_prevObjects != nullptr) {
			for (int i = 0; i < _prevObjects->size(); i++) {
				ToggleObject((*_prevObjects)[i], false);
			}
		}

		// Panning the current set
		for (int i = 0; i < _currentObjects->size(); i++)
			(*_currentObjects)[i].object->Position += (*_currentObjects)[i].panSpeed * deltaTime;
	}
	else {
		// Transition to next set
		_prevObjects = &_objects[currentSet];
		currentSet = (currentSet + 1) % setCount;
		_currentObjects = &_objects[currentSet];
		for (int i = 0; i < _currentObjects->size(); i++) {
			ToggleObject((*_currentObjects)[i], true);
		}
		elapsedTime = 0.0f;
	}
}

void ImagePanning::ToggleObject(ObjectPanningInfo obj, bool enabled)
{
	obj.object->Enabled = enabled;
	if (enabled)
	{
		obj.object->Position = obj.startPos;
		SpriteRenderer* sr = obj.object->GetComponent<SpriteRenderer>();
		if(sr) sr->Color.a = 0.f;
	}
}
