#include <Resources/SoundClipResource.h>

#include <Core/Logger.h>

IResource* SoundClipResource::LoadFromFile(String path)
{
	if (!_sound.loadFromFile(path)) {
		Logger::LogWarning("Failed to load sound clip from file: " + path);
		return nullptr;
	}

	return this;
}
