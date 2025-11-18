
#include <Application.h>
#include <Objects/ObjectManager.h>
#include <Objects/Object.h>
#include <Resources/ResourceManager.h>

#include <Threading/ThreadPool.h>
#include <Threading/IThreadFinishedCallback.h>

#include <Core/Logger.h>

#include <Threading/WorkerTasks/LoadTextureTask.h>
#include <Threading/WorkerTasks/LoadMusicTask.h>
#include <Threading/WorkerTasks/LoadSoundClipTask.h>

#include <Components/Renderers/TextRenderer.h>
#include <Resources/FontResource.h>

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
	TextRenderer* text = circle->AddComponent(new TextRenderer(ResourceManager::LoadFromFile<FontResource>("DefaultFont", "Assets/Fonts/arial.ttf")));
	text->Text = "Loading Resources...";
	text->Alignment = { 0.5f, 0.5f };
	text->RenderLayer = 0;

	ObjectManager::RegisterObject(circle);

	ThreadPool* threadPool = new ThreadPool(2, new SamplePoolFinishedTask());
	threadPool->StartScheduling();

	threadPool->ScheduleTask(new LoadTextureTask("TestTex", "Assets/Images/TestImage1.png", 2000.f, circle, {100.f, 500.f}));
	threadPool->ScheduleTask(new LoadSoundClipTask("TestClip", "Assets/Audio/TestSound1.wav", 4000.f, circle, true));
	threadPool->ScheduleTask(new LoadMusicTask(circle, "Assets/Audio/TestMusic1.mp3", true, 6000.f));

	threadPool->StopWhenCompleted = true;

	// Run The Application
	Application::Instance->Run();
}
