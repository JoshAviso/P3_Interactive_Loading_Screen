#pragma once

#include <Components/Renderers/IRenderer.h>
#include <Objects/Object.h>

#include <Resources/TextureResource.h>

#include <SFML/Graphics.hpp>

class SpriteRenderer : public IRenderer
{
public:
	Vec2 Size;

private:
	sf::Sprite _sprite;
	Shared<TextureResource> _texture;

protected:
	void Render(sf::RenderWindow& window) override {
		_sprite.setPosition(_owner->Position.x, _owner->Position.y);
		_sprite.setRotation(_owner->Rotation);
		_sprite.setScale(_owner->Scale.x * (Size.x / _texture->_texture.getSize().x), _owner->Scale.y * (Size.y / _texture->_texture.getSize().y));
		window.draw(_sprite);
	};

public:
	SpriteRenderer() = default;
	SpriteRenderer(Shared<TextureResource>& texture) {
		SetTexture(texture);
	}
	void SetTexture(Shared<TextureResource>& texture, bool resize = true) {
		if (texture == nullptr) return;
		_sprite.setTexture(texture->_texture);
		_texture = texture;

		Vec2 size = { (float)texture->_texture.getSize().x, (float)texture->_texture.getSize().y };
		_sprite.setOrigin(size.x / 2.f, size.y / 2.f);

		if (resize) Size = size;
	}
};

