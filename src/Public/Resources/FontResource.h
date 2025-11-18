#pragma once

#include <Resources/IResource.h>

#include <SFML/Graphics.hpp>

class FontResource : public IResource
{
private:
	sf::Font _font;

protected:
	IResource* LoadFromFile(String path) override;

	friend class TextRenderer;
	friend class ResourceManager;
};

