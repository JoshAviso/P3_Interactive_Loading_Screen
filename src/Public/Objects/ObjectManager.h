#pragma once

#include <Core/Common.h>
#include <Objects/IObject.h>
#include <Core/Logger.h>

class ObjectManager
{
public:
	template <typename TObject>
	static void RegisterObject(TObject* obj){
		static_assert(std::is_base_of<IObject, TObject>::value, "Pointer must be an object.");
		_instance->_objects.push_back(Unique<IObject>(obj));
	}

	static void RemoveObject(IObject* obj);
	static IObject* FindObjectByName(const String& name);

private:
	List<Unique<IObject>> _objects;

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

