#pragma once

#include <Components/Renderers/IRenderer.h>
#include <Objects/Object.h>

#include <Resources/TextureResource.h>

#include <SFML/Graphics.hpp>

class SpriteRenderer : public IRenderer
{
private:
	sf::Sprite _sprite;

protected:
	void Render(sf::RenderWindow& window) override {
		_sprite.setPosition(_owner->Position.x, _owner->Position.y);
		_sprite.setRotation(_owner->Rotation);
		_sprite.setScale(_owner->Scale.x, _owner->Scale.y);
		window.draw(_sprite);
	};

public:
	SpriteRenderer() = default;
	SpriteRenderer(Shared<TextureResource>& texture) {
		SetTexture(texture);
	}
	void SetTexture(Shared<TextureResource>& texture) {
		_sprite.setTexture(texture->_texture);
		_sprite.setOrigin(texture->_texture.getSize().x / 2.f, texture->_texture.getSize().y / 2.f);
	}
};

