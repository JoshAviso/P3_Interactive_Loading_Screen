#pragma once

#include <Core/Common.h>
#include <Core/String.h>
#include <Math/Vec2.h>

#include <SFML/Graphics.hpp>

#include <Components/IComponent.h>

class IRenderer;

class Object
{
public:
	String Name;
	bool Enabled = true;
	Vec2 Position;
	float Rotation;
	Vec2 Scale;

private:
	List<Unique<IComponent>> _components;

public:
	Object(String name) : Position({ 0.f, 0.f }), Rotation(0.f), Scale({ 1.f, 1.f }), Name(name) {}

	virtual ~Object() = default;
	template <typename TComponent>
	TComponent* AddComponent(TComponent* component) {
		static_assert(std::is_base_of<IComponent, TComponent>::value, "TComponent must inherit from IComponent");

		component->_owner = this;
		_components.push_back(Unique<TComponent>(component));

		return component;
	}
	template <typename TComponent>
	TComponent* GetComponent()
	{
		static_assert(std::is_base_of<IComponent, TComponent>::value, "TComponent must inherit from IComponent");
		for (const auto& component : _components)
		{
			if (TComponent* specificComponent = dynamic_cast<TComponent*>(component.get())) {
				return specificComponent;
			}
		}
		return nullptr;
	}
	template <typename TComponent>
	List<TComponent*> GetComponents()
	{
		static_assert(std::is_base_of<IComponent, TComponent>::value, "TComponent must inherit from IComponent");
		List<TComponent*> componentList{};
		for (const auto& component : _components)
		{
			if (TComponent* specificComponent = dynamic_cast<TComponent*>(component.get())) {
				componentList.push_back(specificComponent);
			}
		}

		return componentList;
	}
	void RemoveComponent(IComponent* component)
	{
		auto it = std::find_if(_components.begin(), _components.end(),
			[component](const Unique<IComponent>& ptr) {
				return ptr.get() == component;
			});
		if (it != _components.end()) {
			_components.erase(it);
		}
	}
	bool Intersects(Vec2 position);

	friend class ObjectManager;
};

