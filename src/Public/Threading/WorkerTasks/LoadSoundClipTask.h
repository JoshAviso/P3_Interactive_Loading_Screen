#pragma once

#include <Threading/WorkerTasks/IWorkerTask.h>

#include <Objects/Object.h>

class LoadSoundClipTask : public IWorkerTask {
public:
	LoadSoundClipTask(String ClipName, String ClipPath, float sleepDelay = 0.f, Object* attachObject = nullptr, bool playImmediately = true);
	void DoWorkerTask(int id) override;

private:
	String _clipName;
	String _clipPath;
	float _sleepDelay;
	Object* _attachObject;
	bool _playImmediately;
};