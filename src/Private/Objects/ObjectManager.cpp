#include <Objects/ObjectManager.h>

#include <algorithm>

void ObjectManager::RemoveObject(Object* obj)
{
	auto it = std::find_if(_instance->_objects.begin(), _instance->_objects.end(),
		[obj](const Unique<Object>& ptr) {
			return ptr.get() == obj;
		});
	if (it != _instance->_objects.end()) {
		_instance->_objects.erase(it);
	}
}
Object* ObjectManager::FindObjectByName(const String& name)
{
	for (int i = 0; i < _instance->_objects.size(); i++) {
		if (_instance->_objects[i]->Name == name) {
			return _instance->_objects[i].get();
		}
	}
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
	List<IRenderer*> renderers{};
	for (int i = 0; i < _objects.size(); i++)
	{
		List<IRenderer*> renderComponents = _objects[i]->GetComponents<IRenderer>();
		for (int j = 0; j < renderComponents.size(); j++)
		{
			renderers.push_back(renderComponents[j]);
		}
	}

	std::stable_sort(renderers.begin(), renderers.end(), 
		[](IRenderer* a, IRenderer* b) {
			return a->RenderLayer < b->RenderLayer;
		});

	for (int i = 0; i < renderers.size(); i++) {
		renderers[i]->Render(window);
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
