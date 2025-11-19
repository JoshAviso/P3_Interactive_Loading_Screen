
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
#include <Components/Update/EnemyController.h>
#include <Components/Renderers/ShapeRenderers/PolygonRenderer.h>

#include <Components/Update/EnemySpawner.h>
#include <Components/Update/ScoreUpdater.h>

Object* loadedImage1;
Object* loadedImage2;
Object* loadedImage3;

Object* bg1;
Object* bg2;
Object* chara1;
Object* chara2;

Object* circle;
Object* fpsCounter;
Object* scoreDisplay;
Object* player;
Object* enemySpawner;
Object* loadingText;
TextRenderer* loadText;

class SamplePoolFinishedTask : public IThreadFinishedCallback
{
	void OnThreadFinished(int id) override
	{
		Logger::Log("Sample Pool Finished");

		loadText->Text = "Loading Complete!";

		IThread::Sleep(2000);

		//Render loaded images
		loadedImage1->Enabled = true;
		loadedImage2->Enabled = true;
		loadedImage3->Enabled = true;

		//Removing loading screen objects
		ObjectManager::RemoveObject(bg1);
		ObjectManager::RemoveObject(bg2);
		ObjectManager::RemoveObject(chara1);
		ObjectManager::RemoveObject(chara2);
		ObjectManager::RemoveObject(circle);
		ObjectManager::RemoveObject(scoreDisplay);
		ObjectManager::RemoveObject(loadingText);

		player->GetComponent<CharacterController>()->DisableBullets();
		enemySpawner->GetComponent<EnemySpawner>()->DisableEnemies();
		ObjectManager::RemoveObject(player);
		ObjectManager::RemoveObject(enemySpawner);
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
	fpsCounter = ObjectManager::RegisterObject(new Object("FPSCounter"));
	fpsCounter->Position = { 10.0f, 10.0f };
	TextRenderer* fpsText = fpsCounter->AddComponent(new TextRenderer(arialFont));
	fpsText->FontSize = 24;
	fpsText->RenderLayer = 999;
	fpsText->Text = "0fps";
	fpsCounter->AddComponent(new FPSCounterUpdater(0.5f));

	//Loading Text
	loadingText = ObjectManager::RegisterObject(new Object("LoadingText"));
	loadingText->Position = { 10.0f, 690.0f };
	loadText = loadingText->AddComponent(new TextRenderer(arialFont));
	loadText->FontSize = 24;
	loadText->RenderLayer = 999;
	loadText->Text = "Loading...";

	// Score Display
	scoreDisplay = ObjectManager::RegisterObject(new Object("ScoreDisplay"));
	scoreDisplay->Position = { Application::WindowSize().x / 2.f, 100.f };
	TextRenderer* scoreText = scoreDisplay->AddComponent(new TextRenderer(arialFont));
	scoreText->FontSize = 36;
	scoreText->RenderLayer = 100;
	scoreText->Alignment = { 0.5, 0.5f };
	scoreDisplay->AddComponent(new ScoreUpdater());

	// Player
	player = ObjectManager::RegisterObject(new Object("Player"));
	player->Position = {Application::WindowSize().x / 2.f, Application::WindowSize().y / 2.f};
	player->AddComponent(new CharacterController({200.f, { 0.f, 0.f }}));
	player->AddComponent(new TriangleRenderer(10.f))->RenderLayer = 10;

	// Enemy Spawner
	enemySpawner = ObjectManager::RegisterObject(new Object("EnemySpawner"));
	enemySpawner->AddComponent(new EnemySpawner({ {200.f, 200.f} }));

	circle = new Object("Circle");
	circle->Position = { 400.0f, 300.0f };
	//TextRenderer* text = circle->AddComponent(new TextRenderer(arialFont));
	//text->Text = "Loading Resources...";
	//text->Alignment = { 0.5f, 0.5f };
	//text->RenderLayer = 0;
	
	//Images for loading screen
	bg1 = ObjectManager::RegisterObject(new Object("BG1"));
	bg1->AddComponent(new SpriteRenderer(ResourceManager::LoadFromFile<TextureResource>("BG1Tex", "Assets/Images/BG5.jpg")))
		->Size = { 1000.f, 600.f };
	bg1->Scale = { 1.6f, 1.6f };

	chara1 = ObjectManager::RegisterObject(new Object("CHARA1"));
	SpriteRenderer* sp1 = chara1->AddComponent(new SpriteRenderer(ResourceManager::LoadFromFile<TextureResource>("Chara1Tex", "Assets/Images/motoko.png")));
	sp1->Size = { 513.f, 600.f };
	sp1->RenderLayer = 20;
	chara1->Scale = { 1.4f, 1.4f };
	//chara1->AddComponent(new MouseDetectScript());

	bg2 = ObjectManager::RegisterObject(new Object("BG2"));
	bg2->AddComponent(new SpriteRenderer(ResourceManager::LoadFromFile<TextureResource>("BG2Tex", "Assets/Images/BG4.jpg")))
		->Size = { 1000.f, 600.f };
	bg2->Scale = { 1.6f, 1.6f };

	chara2 = ObjectManager::RegisterObject(new Object("CHARA2"));
	SpriteRenderer* sp2 = chara2->AddComponent(new SpriteRenderer(ResourceManager::LoadFromFile<TextureResource>("Chara2Tex", "Assets/Images/spike.png")));
	sp2->Size = { 513.f, 525.f };
	sp2->RenderLayer = 20;
	chara2->Scale = { 1.4f, 1.4f };
	//chara2->AddComponent(new MouseDetectScript());

	//Panning the images
	List<ImagePanning::ObjectPanningInfo> panningObjects = {
		{ bg1,		{650.f, 350.f},		{5.f, 2.f},		0.4f, 0 },
		{ chara1,	{340.f, 440.f},		{-5.f, -2.f},	0.8f, 0 },
		{ bg2,		{650.f, 350.f},		{-5.f, -2.f},	0.4f, 1 },
		{ chara2,	{940.f, 440.f},		{5.f, 2.f},		0.8f, 1 }
	};

	ObjectManager::RegisterObject(new Object("Panner"))
		->AddComponent(new ImagePanning(8.f, 1.f, panningObjects));

	ObjectManager::RegisterObject(circle);

	//Big images
	loadedImage1 = ObjectManager::RegisterObject(new Object("LoadedImage1"));
	loadedImage1->Position = { 100, 350 };

	loadedImage2 = ObjectManager::RegisterObject(new Object("LoadedImage2"));
	loadedImage2->Position = { 550, 350 };

	loadedImage3 = ObjectManager::RegisterObject(new Object("LoadedImage3"));
	loadedImage3->Position = { 1050, 350 };

	//Disable objects until all 3 are loaded
	loadedImage1->Enabled = false;
	loadedImage2->Enabled = false;
	loadedImage3->Enabled = false;

	//Scheduling threads
	ThreadPool* threadPool = new ThreadPool(5, new SamplePoolFinishedTask());
	threadPool->StartScheduling();

	threadPool->ScheduleTask(new LoadSoundClipTask("TestClip", "Assets/Audio/TestSound1.wav", 2000.f, circle, true));
	threadPool->ScheduleTask(new LoadMusicTask(circle, "Assets/Audio/TestMusic1.mp3", true, 4000.f));

	threadPool->ScheduleTask(new LoadTextureTask("LoadedImage1Tex", "Assets/Images/LoadedImage1.png", 5000.f, loadedImage1, { 500.f, 800.f }));
	threadPool->ScheduleTask(new LoadTextureTask("LoadedImage2Tex", "Assets/Images/LoadedImage2.png", 8000.f, loadedImage2, { 500.f, 800.f }));
	threadPool->ScheduleTask(new LoadTextureTask("LoadedImage3Tex", "Assets/Images/LoadedImage3.png", 11000.f, loadedImage3, { 500.f, 800.f }));
	
	threadPool->StopWhenCompleted = true;

	// Run The Application
	Application::Instance->Run();
}
