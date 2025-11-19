
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
#include <Components/Renderers/SpriteRenderer.h>
#include <Resources/ResourceManager.h>

#include <Components/Update/MouseDetectScript.h>

#include <Components/Update/CharacterController.h>
#include <Components/Renderers/ShapeRenderers/TriangleRenderer.h>

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

	// Player
	Object* player = ObjectManager::RegisterObject(new Object("Player"));
	player->Position = {Application::WindowSize().x / 2.f, Application::WindowSize().y / 2.f};
	player->AddComponent(new CharacterController({200.f, { 0.f, 0.f }}));
	player->AddComponent(new TriangleRenderer(10.f))->RenderLayer = 10;

	Object* circle = new Object("Circle");
	circle->Position = { 400.0f, 300.0f };
	//TextRenderer* text = circle->AddComponent(new TextRenderer(arialFont));
	//text->Text = "Loading Resources...";
	//text->Alignment = { 0.5f, 0.5f };
	//text->RenderLayer = 0;

	Object* bg1 = ObjectManager::RegisterObject(new Object("BG1"));
	bg1->AddComponent(new SpriteRenderer(ResourceManager::LoadFromFile<TextureResource>("BG1Tex", "Assets/Images/BG5.jpg")))
		->Size = { 1000.f, 600.f };
	bg1->Scale = { 1.6f, 1.6f };

	Object* chara1 = ObjectManager::RegisterObject(new Object("CHARA1"));
	SpriteRenderer* sp1 = chara1->AddComponent(new SpriteRenderer(ResourceManager::LoadFromFile<TextureResource>("Chara1Tex", "Assets/Images/motoko.png")));
	sp1->Size = { 513.f, 600.f };
	sp1->RenderLayer = 20;
	chara1->Scale = { 1.4f, 1.4f };
	//chara1->AddComponent(new MouseDetectScript());

	Object* bg2 = ObjectManager::RegisterObject(new Object("BG2"));
	bg2->AddComponent(new SpriteRenderer(ResourceManager::LoadFromFile<TextureResource>("BG2Tex", "Assets/Images/BG4.jpg")))
		->Size = { 1000.f, 600.f };
	bg2->Scale = { 1.6f, 1.6f };

	Object* chara2 = ObjectManager::RegisterObject(new Object("CHARA2"));
	SpriteRenderer* sp2 = chara2->AddComponent(new SpriteRenderer(ResourceManager::LoadFromFile<TextureResource>("Chara2Tex", "Assets/Images/spike.png")));
	sp2->Size = { 513.f, 525.f };
	sp2->RenderLayer = 20;
	chara2->Scale = { 1.4f, 1.4f };
	//chara2->AddComponent(new MouseDetectScript());

	List<ImagePanning::ObjectPanningInfo> panningObjects = {
		{ bg1,		{650.f, 350.f},		{5.f, 2.f},		0.4f, 0 },
		{ chara1,	{340.f, 440.f},		{-5.f, -2.f},	0.8f, 0 },
		{ bg2,		{650.f, 350.f},		{-5.f, -2.f},	0.4f, 1 },
		{ chara2,	{940.f, 440.f},		{5.f, 2.f},		0.8f, 1 }
	};

	ObjectManager::RegisterObject(new Object("Panner"))
		->AddComponent(new ImagePanning(8.f, 1.f, panningObjects));

	ObjectManager::RegisterObject(circle);

	ThreadPool* threadPool = new ThreadPool(2, new SamplePoolFinishedTask());
	threadPool->StartScheduling();

	threadPool->ScheduleTask(new LoadSoundClipTask("TestClip", "Assets/Audio/TestSound1.wav", 4000.f, circle, true));
	threadPool->ScheduleTask(new LoadMusicTask(circle, "Assets/Audio/TestMusic1.mp3", true, 6000.f));
	
	threadPool->StopWhenCompleted = true;

	// Run The Application
	Application::Instance->Run();
}
