
#include <Threading/WorkerTasks/LoadTextureTask.h>

#include <Threading/IThread.h>
#include <Components/Renderers/SpriteRenderer.h>
#include <Resources/ResourceManager.h>
#include <Resources/TextureResource.h>

#include <Core/Logger.h>

LoadTextureTask::LoadTextureTask(String TexName, String TexPath, float sleepDelay, Object* attachObject, Vec2 drawSize) 
	: _texName(TexName), _texPath(TexPath), _sleepDelay(sleepDelay), _attachObject(attachObject), _drawSize(drawSize) {}

void LoadTextureTask::DoWorkerTask(int id)
{
	if (_sleepDelay > 0.f) IThread::Sleep((uint)_sleepDelay);

	Shared<TextureResource> tex = ResourceManager::LoadFromFile<TextureResource>(_texName, _texPath);
	
	if (_attachObject != nullptr) {
		SpriteRenderer* sprite = _attachObject->AddComponent(new SpriteRenderer(tex));
		if (_drawSize != Vec2({ -1.f, -1.f })) {
			sprite->Size = _drawSize;
		}
	}
}
