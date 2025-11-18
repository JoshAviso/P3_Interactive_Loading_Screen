#include <Resources/FontResource.h>

#include <Core/Logger.h>

IResource* FontResource::LoadFromFile(String path)
{
	if (!_font.loadFromFile(path)) {
		Logger::LogWarning("Failed to load font from file: " + path);
		return nullptr;
	}

	return this;
}
