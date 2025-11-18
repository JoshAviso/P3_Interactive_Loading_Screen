
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
#include <Components/Update/FPSCounterUpdater.h>
#include <Components/Update/ImagePanning.h>

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
		{1280, 720},
		160
	});

	Shared<FontResource> arialFont = ResourceManager::LoadFromFile<FontResource>("DefaultFont", "Assets/Fonts/arial.ttf");

	// FPS Counter
	Object* fpsCounter = ObjectManager::RegisterObject(new Object("FPSCounter"));
	fpsCounter->Position = { 10.0f, 10.0f };
	TextRenderer* fpsText = fpsCounter->AddComponent(new TextRenderer(arialFont));
	fpsText->FontSize = 24;
	fpsText->RenderLayer = 999;
	fpsText->Text = "0fps";
	fpsCounter->AddComponent(new FPSCounterUpdater(0.5f));

	Object* circle = new Object("Circle");
	circle->Position = { 400.0f, 300.0f };
	TextRenderer* text = circle->AddComponent(new TextRenderer(arialFont));
	text->Text = "Loading Resources...";
	text->Alignment = { 0.5f, 0.5f };
	text->RenderLayer = 0;

	Object* bg1 = new Object("BG1");
	bg1->Position = {650.0f, 350.0f};
	bg1->AddComponent(new ImagePanning(0.08f, 0));

	Object* chara1 = new Object("CHARA1");
	chara1->Position = { 640.0f, 440.0f };
	chara1->AddComponent(new ImagePanning(0.08f, 0));

	Object* bg2 = new Object("BG2");
	bg2->Position = { 650.0f, 350.0f };
	bg2->AddComponent(new ImagePanning(-0.08f, 0));

	Object* chara2 = new Object("CHARA2");
	chara2->Position = { 640.0f, 440.0f };
	chara2->AddComponent(new ImagePanning(-0.08f, 0));

	ObjectManager::RegisterObject(circle);
	ObjectManager::RegisterObject(bg1);
	ObjectManager::RegisterObject(chara1);
	ObjectManager::RegisterObject(bg2);
	ObjectManager::RegisterObject(chara2);

	ThreadPool* threadPool = new ThreadPool(2, new SamplePoolFinishedTask());
	threadPool->StartScheduling();

	threadPool->ScheduleTask(new LoadTextureTask("BG1Tex", "Assets/Images/BG5.jpg", 0.0f, bg1, { 1000.f, 600.f }));
	threadPool->ScheduleTask(new LoadTextureTask("Chara1Tex", "Assets/Images/motoko.png", 0.0f, chara1, { 513.f, 600.f }));

	threadPool->ScheduleTask(new LoadTextureTask("BG2Tex", "Assets/Images/BG4.jpg", 2000.0f, bg2, { 1000.f, 600.f }));
	threadPool->ScheduleTask(new LoadTextureTask("Chara2Tex", "Assets/Images/spike.png", 2000.0f, chara2, { 513.f, 525.f }));

	threadPool->ScheduleTask(new LoadTextureTask("TestTex", "Assets/Images/TestImage1.png", 2000.f, circle, {100.f, 500.f}));
	threadPool->ScheduleTask(new LoadSoundClipTask("TestClip", "Assets/Audio/TestSound1.wav", 4000.f, circle, true));
	threadPool->ScheduleTask(new LoadMusicTask(circle, "Assets/Audio/TestMusic1.mp3", true, 6000.f));
	
	threadPool->StopWhenCompleted = true;

	// Run The Application
	Application::Instance->Run();
}
