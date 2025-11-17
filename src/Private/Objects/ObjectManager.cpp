#include <Objects/ObjectManager.h>


void ObjectManager::RemoveObject(Object* obj)
{
}
Object* ObjectManager::FindObjectByName(const String& name)
{
    return nullptr;
}

void ObjectManager::Update(float deltaTime)
{
	for (int i = 0; i < _objects.size(); i++)
	{
		List<IUpdateComponent*> updateComponents = _objects[i]->GetComponents<IUpdateComponent>();
		for (int j = 0; j < updateComponents.size(); j++)
		{
			updateComponents[j]->Update(deltaTime);
		}
	}
}

void ObjectManager::RenderObjectsTo(sf::RenderWindow& window)
{
	for (int i = 0; i < _objects.size(); i++)
	{
		List<IRenderer*> renderComponents = _objects[i]->GetComponents<IRenderer>();
		for (int j = 0; j < renderComponents.size(); j++)
		{
			renderComponents[j]->Render(window);
		}
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
