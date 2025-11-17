
#include <Threading/WorkerTasks/LoadSoundClipTask.h>

#include <Threading/IThread.h>
#include <Components/Update/AudioSourceComponent.h>
#include <Resources/ResourceManager.h>
#include <Resources/SoundClipResource.h>

#include <Core/Logger.h>

LoadSoundClipTask::LoadSoundClipTask(String ClipName, String ClipPath, float sleepDelay, Object* attachObject, bool playImmediately)
	: _clipName(ClipName), _clipPath(ClipPath), _sleepDelay(sleepDelay), _attachObject(attachObject), _playImmediately(playImmediately) {}

void LoadSoundClipTask::DoWorkerTask(int id)
{
	if (_sleepDelay > 0.f) IThread::Sleep((uint)_sleepDelay);

	Shared<SoundClipResource> clip = ResourceManager::LoadFromFile<SoundClipResource>(_clipName, _clipPath);
	
	if (_attachObject != nullptr) {
		AudioSourceComponent* sound = _attachObject->AddComponent(new AudioSourceComponent(clip));
		if (_playImmediately) sound->Play();
	}
}
