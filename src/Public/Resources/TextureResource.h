#pragma once

#include <Resources/IResource.h>

#include <SFML/Graphics.hpp>

class TextureResource : public IResource
{
private:
	sf::Texture _texture;

protected:
	IResource* LoadFromFile(String path) override;

	friend class SpriteRenderer;
	friend class ResourceManager;
};

