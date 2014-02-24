#pragma once
#include "TextComponent.hpp"
#include "FontManager.hpp"

TextComponent::TextComponent(void)
{
	bitMask = ComponentBitMasks::TextComponent;
	text = new sf::Text();
	SetFontFace("arial");
	SetFontSize(12);
	SetOriginalColor(sf::Color::White);
	SetJustification(TextJustification::TopLeft);
	SetTextString("NO_STRING_DECLARED");
}

TextComponent::TextComponent(std::string fontName, int fontsize, sf::Color fontColor, std::string string)
{
	bitMask = ComponentBitMasks::TextComponent;
	text = new sf::Text();
	SetFontFace(fontName);
	SetFontSize(fontsize);
	SetOriginalColor(fontColor);
	SetJustification(TextJustification::TopLeft);
	SetTextString(string);
}

TextComponent::~TextComponent(void)
{
	delete text;
}

void TextComponent::SetFontSize(int size)
{
	text->setCharacterSize(size);
}

void TextComponent::SetFontFace(std::string name)
{
	font = FontManager::GetFont(name);
	text->setFont(font);
}

void TextComponent::SetTextString(std::string string)
{
	text->setString(string);
}

void TextComponent::SetOriginalColor(sf::Color color)
{
	originalColor = color;
	text->setColor(color);
}

void TextComponent::SetCurrentColor(sf::Color color)
{
	text->setColor(color);
}

void TextComponent::SetJustification(TextJustification::TextJustification justification)
{
	this->justification = justification;
}

void TextComponent::SetPosition(sf::Vector2f position)
{
	text->setPosition(position.x, position.y);
}

sf::Color TextComponent::GetOriginalColor(void) const
{
	return originalColor;
}

sf::Color TextComponent::GetCurrentColor(void) const
{
	return text->getColor();
}

sf::Text* TextComponent::GetTextString(void) const
{
	return text;
}

sf::FloatRect TextComponent::GetGlobalBounds(void) const
{
	return text->getGlobalBounds();
}

sf::FloatRect TextComponent::GetLocalBounds(void) const
{
	return text->getLocalBounds();
}

TextJustification::TextJustification TextComponent::GetJustification(void) const
{
	return justification;
}