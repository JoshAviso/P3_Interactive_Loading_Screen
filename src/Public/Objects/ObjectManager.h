#pragma once

#include <Core/Common.h>
#include <Objects/IObject.h>

class ObjectManager
{
public:
	void RegisterObject(IObject* obj);
	void RemoveObject(IObject* obj);
	IObject* FindObjectByName(const String& name);

private:
	List<Unique<IObject>> _objects;

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

