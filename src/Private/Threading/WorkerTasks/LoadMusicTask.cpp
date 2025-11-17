
#include <Threading/WorkerTasks/LoadMusicTask.h>

#include <Threading/IThread.h>
#include <Components/Update/AudioSourceComponent.h>

LoadMusicTask::LoadMusicTask(Object* attachObject, String MusicPath, bool playImmediately, float sleepDelay) 
	: _attachObject(attachObject), _musicPath(MusicPath), _playImmediately(playImmediately), _sleepDelay(sleepDelay) {}

void LoadMusicTask::DoWorkerTask(int id)
{
	if (_attachObject == nullptr) {
		return;
	}
	if (_sleepDelay > 0.f) IThread::Sleep((uint)_sleepDelay);

	AudioSourceComponent* music = _attachObject->AddComponent(new AudioSourceComponent(_musicPath));
	if (_playImmediately) music->Play();
}
