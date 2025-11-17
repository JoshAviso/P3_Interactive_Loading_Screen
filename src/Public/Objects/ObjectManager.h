#pragma once

#include <Core/Common.h>
#include <Objects/Object.h>
#include <Core/Logger.h>

#include <Components/Update/IUpdateComponent.h>
#include <Components/Renderers/IRenderer.h>

class ObjectManager
{
public:
	template <typename TObject>
	static void RegisterObject(TObject* obj){
		static_assert(std::is_base_of<Object, TObject>::value, "Pointer must be an object.");
		_instance->_objects.push_back(Unique<Object>(obj));
	}

	static void RemoveObject(Object* obj);
	static Object* FindObjectByName(const String& name);

private:
	List<Unique<Object>> _objects;

	void Update(float deltaTime);
	void RenderObjectsTo(sf::RenderWindow& window);

// SINGLETON
public:
	static ObjectManager* Initialize();
private:
	static ObjectManager* _instance;
	explicit ObjectManager();
	~ObjectManager();
	ObjectManager(const ObjectManager&) = delete;
	ObjectManager& operator=(const ObjectManager&) = delete;

public:
	friend class Application;
};

