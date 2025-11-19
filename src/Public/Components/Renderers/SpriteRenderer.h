#pragma once

#include <Components/Renderers/IRenderer.h>
#include <Objects/Object.h>

#include <Resources/TextureResource.h>

#include <SFML/Graphics.hpp>
#include <Core/Color.h>

class SpriteRenderer : public IRenderer
{
public:
	Vec2 Size = {0.f, 0.f};
	Color Color = Color::White();

private:
	sf::Sprite _sprite;
	sf::Image _cachedCollisionCheckImg;
	Shared<TextureResource> _texture;

protected:
	void Render(sf::RenderWindow& window) override {
		_sprite.setColor(Color);
		_sprite.setPosition(_owner->Position.x, _owner->Position.y);
		_sprite.setRotation(_owner->Rotation);
		_sprite.setScale(_owner->Scale.x * (Size.x / _texture->_texture.getSize().x), _owner->Scale.y * (Size.y / _texture->_texture.getSize().y));
		window.draw(_sprite);
	};

public:
	SpriteRenderer() = default;
	SpriteRenderer(Shared<TextureResource> texture) {
		SetTexture(texture);
	}
	void SetTexture(Shared<TextureResource> texture, bool resize = true) {
		if (texture == nullptr) {
			_cachedCollisionCheckImg = sf::Image();
			return;
		}
		_sprite.setTexture(texture->_texture);
		_texture = texture;

		Vec2 size = { (float)texture->_texture.getSize().x, (float)texture->_texture.getSize().y };
		_sprite.setOrigin(size.x / 2.f, size.y / 2.f);

		if (resize) Size = size;

		_cachedCollisionCheckImg = _texture->_texture.copyToImage();
	}
	bool Intersects(Vec2 position) {
		if (!_owner || !_owner->Enabled) return false;
		if (_texture == nullptr) return false;

		sf::FloatRect bounds = _sprite.getGlobalBounds();
		if (!bounds.contains(position.x, position.y)) return false;

		sf::Vector2f localPos = _sprite.getInverseTransform().transformPoint(position.x, position.y);
		sf::Color pixColor = _cachedCollisionCheckImg.getPixel(localPos.x, localPos.y);

		return pixColor.a > 0;
	}
};

