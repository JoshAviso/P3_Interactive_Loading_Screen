
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

int main()
{
	Application::Initialize({
		"P3 Interactive Loading Screen | Aviso & Taylan",
		{800, 600} 
	});

	// Resource Loading
	Shared<TextureResource> testTex = ResourceManager::LoadFromFile<TextureResource>("TestTexture", "Assets/Images/TestImage1.png");
	Shared<SoundClipResource> testSound = ResourceManager::LoadFromFile<SoundClipResource>("TestSound", "Assets/Audio/TestSound1.wav");

	// Object Declarations
	Object* circle = new Object("Circle");
	circle->AddComponent(new SpriteRenderer(testTex))->Size = {200.f, 100.f};
	circle->AddComponent(new AudioSourceComponent(testSound));
	circle->AddComponent(new AudioSourceComponent("Assets/Audio/TestMusic1.mp3"))->Play();

	//circle->AddComponent(new RectangleRenderer(Vec2({ 50.0f, 100.f })));

	circle->Position = { 400.0f, 300.0f };
	ObjectManager::RegisterObject(circle);

	// Run The Application
	Application::Instance->Run();
}
