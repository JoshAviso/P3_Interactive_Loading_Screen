
#include <Application.h>
#include <Objects/ObjectManager.h>
#include <Objects/Object.h>
#include <Components/Renderers/ShapeRenderers/RectangleRenderer.h>
#include <Components/Renderers/ShapeRenderers/CircleRenderer.h>

int main()
{
	Application::Initialize({
		"P3 Interactive Loading Screen | Aviso & Taylan",
		{800, 600} 
	});

	Object* circle = new Object("Circle");
	circle->AddComponent(new RectangleRenderer(Vec2({ 50.0f, 100.f })));

	circle->Position = { 400.0f, 300.0f };
	ObjectManager::RegisterObject(circle);

	Application::Instance->Run();
}
