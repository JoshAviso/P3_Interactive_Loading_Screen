#include <Resources/TextureResource.h>

#include <Core/Logger.h>

IResource* TextureResource::LoadFromFile(String path)
{
	if (!_texture.loadFromFile(path)) {
		Logger::LogWarning("Failed to load texture from file: " + path);
		return nullptr;
	}

	return this;
}
