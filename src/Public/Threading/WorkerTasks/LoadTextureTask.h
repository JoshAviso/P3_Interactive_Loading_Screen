#pragma once

#include <Threading/WorkerTasks/IWorkerTask.h>

#include <Objects/Object.h>

class LoadTextureTask : public IWorkerTask {
public:
	LoadTextureTask(String TexName, String TexPath, float sleepDelay = 0.f, Object* attachObject = nullptr, Vec2 drawSize = {-1.f, -1.f});
	void DoWorkerTask(int id) override;

private:
	String _texName;
	String _texPath;
	float _sleepDelay;
	Object* _attachObject;
	Vec2 _drawSize;
};