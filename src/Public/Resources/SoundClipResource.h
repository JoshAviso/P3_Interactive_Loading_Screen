#pragma once

#include <Resources/IResource.h>

#include <SFML/Audio.hpp>

class SoundClipResource : public IResource 
{

private:
	sf::SoundBuffer _sound;

protected:
	IResource* LoadFromFile(String path) override;

	friend class AudioSourceComponent;
	friend class ResourceManager;
};

