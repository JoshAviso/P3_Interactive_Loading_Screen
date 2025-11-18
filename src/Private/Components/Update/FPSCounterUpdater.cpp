#include <Components/Update/FPSCounterUpdater.h>

#include <Objects/Object.h>
#include <Core/Logger.h>

void FPSCounterUpdater::Update(float deltaTime)
{
	if (_text == nullptr) _text = _owner->GetComponent<TextRenderer>();

	_accumulatedTime += deltaTime;
	_frameCount++;

	if (_accumulatedTime >= UpdateFrequency)
	{
		float fps = static_cast<float>(_frameCount) / _accumulatedTime;
		if (_text != nullptr)
		{
			_text->Text = std::to_string(static_cast<int>(fps)) + "fps";
		}

		_accumulatedTime = 0.f;
		_frameCount = 0;
	}
}
