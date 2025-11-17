
#include <Application.h>
#include <Objects/ObjectManager.h>
#include <Objects/Object.h>
#include <Resources/ResourceManager.h>
#include <Resources/TextureResource.h>
#include <Components/Renderers/ShapeRenderers/RectangleRenderer.h>
#include <Components/Renderers/ShapeRenderers/CircleRenderer.h>
#include <Components/Renderers/SpriteRenderer.h>

#include <Components/Update/AudioSourceComponent.h>
#include <Resources/SoundClipResource.h>

#include <Threading/WorkerTasks/IWorkerTask.h>
#include <Threading/ThreadPool.h>
#include <Threading/IThreadFinishedCallback.h>

#include <Core/Logger.h>

#include <Threading/WorkerTasks/LoadTextureTask.h>

class SampleLoadMusicTask : public IWorkerTask
{
public:
	Object* _obj;
	SampleLoadMusicTask(Object* obj) : _obj(obj) {}
	void DoWorkerTask(int id) override
	{

	}
};

class SampleLoadSoundTask : public IWorkerTask
{
public:
	Object* _obj;
	SampleLoadSoundTask(Object* obj) : _obj(obj) {}
	void DoWorkerTask(int id) override
	{

	}
};


class SamplePoolFinishedTask : public IThreadFinishedCallback
{
	void OnThreadFinished(int id) override
	{
		Logger::Log("Sample Pool Finished");
	}
};

int main()
{
	Application::Initialize({
		"P3 Interactive Loading Screen | Aviso & Taylan",
		{800, 600} 
	});

	Object* circle = new Object("Circle");
	circle->Position = { 400.0f, 300.0f };
	ObjectManager::RegisterObject(circle);

	ThreadPool* threadPool = new ThreadPool(2, new SamplePoolFinishedTask());
	threadPool->StartScheduling();

	threadPool->ScheduleTask(new LoadTextureTask("TestTex", "Assets/Images/TestImage1.png", 2000.f, circle, {100.f, 500.f}));
	threadPool->StopWhenCompleted = true;

	// Resource Loading
	//Shared<SoundClipResource> testSound = ResourceManager::LoadFromFile<SoundClipResource>("TestSound", "Assets/Audio/TestSound1.wav");

	// Object Declarations
	//circle->AddComponent(new AudioSourceComponent(testSound));
	//circle->AddComponent(new AudioSourceComponent("Assets/Audio/TestMusic1.mp3"))->Play();

	// Run The Application
	Application::Instance->Run();
}
