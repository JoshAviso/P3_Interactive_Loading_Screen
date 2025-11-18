#pragma once

#include <Components/Renderers/IRenderer.h>
#include <SFML/Graphics.hpp>

#include <Core/Common.h>
#include <Core/String.h>
#include <Core/Color.h>

#include <Objects/Object.h>

#include <Resources/FontResource.h>

class TextRenderer : public IRenderer
{
public:
	String Text = String();
	Shared<FontResource> Font = nullptr;
	uint FontSize = 24;
	Color FontColor = Color::White();
	Color OutlineColor = Color::Black();
	float OutlineThickness = 0.f;
	Vec2 Alignment = { 0.f, 0.f };
	bool IsBold = false;
	bool IsItalic = false;
	bool IsUnderlined = false;

private:
	sf::Text _text;

protected:
	void Render(sf::RenderWindow& window) override {
		if (Font == nullptr) return;

		_text.setFont(Font->_font);
		_text.setString(Text);
		_text.setCharacterSize(FontSize);
		_text.setFillColor(sf::Color(FontColor.r, FontColor.g, FontColor.b, FontColor.a));
		_text.setOutlineColor(sf::Color(OutlineColor.r, OutlineColor.g, OutlineColor.b, OutlineColor.a));
		_text.setOutlineThickness(OutlineThickness);
		sf::Uint32 style = sf::Text::Regular;
		if (IsBold) style |= sf::Text::Bold;
		if (IsItalic) style |= sf::Text::Italic;
		if (IsUnderlined) style |= sf::Text::Underlined;
		_text.setStyle(style);

		sf::FloatRect textRect = _text.getLocalBounds();
		_text.setOrigin(textRect.left + textRect.width * Alignment.x, textRect.top + textRect.height * Alignment.y);

		_text.setPosition(_owner->Position.x, _owner->Position.y);
		_text.setRotation(_owner->Rotation);
		_text.setScale(_owner->Scale.x, _owner->Scale.y);

		window.draw(_text);
	};

public:
	TextRenderer() = default;
	TextRenderer(Shared<FontResource> font) : Font(font) {}
};

