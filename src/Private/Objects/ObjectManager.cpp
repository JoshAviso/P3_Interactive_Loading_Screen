#include <Objects/ObjectManager.h>


void ObjectManager::RemoveObject(IObject* obj)
{
}
IObject* ObjectManager::FindObjectByName(const String& name)
{
    return nullptr;
}

void ObjectManager::Update(float deltaTime)
{
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->Update(deltaTime);
	}
}

void ObjectManager::RenderObjectsTo(sf::RenderWindow& window)
{
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->DrawTo(window);
	}
}

// SINGLETON 
ObjectManager* ObjectManager::_instance = nullptr;
ObjectManager* ObjectManager::Initialize()
{
    if (_instance != nullptr) return _instance;

    _instance = new ObjectManager();
    return _instance;
}

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager() {}
