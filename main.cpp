
#include <Application.h>
#include <Objects/ObjectManager.h>
#include <Objects/Shapes/RectangleShape.h>
#include <Objects/Shapes/CircleShape.h>

int main()
{
	Application::Initialize({
		"P3 Interactive Loading Screen | Aviso & Taylan",
		{800, 600} 
	});

	CircleShape* circle = new CircleShape(10.0f);
	circle->Position = { 100.0f, 100.0f };
	circle->Name = "MyCircle";
	ObjectManager::RegisterObject(circle);

	Application::Instance->Run();
}
