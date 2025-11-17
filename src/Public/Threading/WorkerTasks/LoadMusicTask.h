#pragma once

#include <Threading/WorkerTasks/IWorkerTask.h>

#include <Objects/Object.h>

class LoadMusicTask : public IWorkerTask {
public:
	LoadMusicTask(Object* attachObject, String MusicPath, bool playImmediately = true, float sleepDelay = 0.f);
	void DoWorkerTask(int id) override;

private:
	Object* _attachObject;
	String _musicPath;
	bool _playImmediately;
	float _sleepDelay;
};