#pragma once

#include <Core/Common.h>
#include <Core/String.h>
#include <Resources/IResource.h>

#include <stdexcept>

class ResourceManager
{
public:
	template <typename TResource>
	static Shared<TResource> LoadFromFile(String name, String path) {
		static_assert(std::is_base_of<IResource, TResource>::value, "TResource must be a valid resource type.");

		if (_instance->_resources.find(name) != _instance->_resources.end()) {
			auto casted = std::dynamic_pointer_cast<TResource>(_instance->_resources[name]);
			if (!casted) {
				throw std::runtime_error("Stored resource type mismatch for key: " + name);
			}
			return casted;
		}

		Shared<TResource> resource = Make_Shared<TResource>();
		if (resource->LoadFromFile(path)) {
			_instance->_resources[name] = resource;
			return resource;
		}

		return nullptr;
	}

	template <typename TResource>
	static Shared<TResource> GetResource(String name) {
		static_assert(std::is_base_of<IResource, TResource>::value, "TResource must be a valid resource type.");

		if (_instance->_resources.find(name) != _instance->_resources.end()) {
			auto casted = std::dynamic_pointer_cast<TResource>(_instance->_resources[name]);
			if (!casted) {
				throw std::runtime_error("Stored resource type mismatch for key: " + name);
			}
			return casted;
		}
		return nullptr;
	}

private:
	Dict<String, Shared<IResource>> _resources;

// SINGLETON
public:
	static ResourceManager* Initialize();
private:
	static ResourceManager* _instance;
	explicit ResourceManager();
	~ResourceManager();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

};

