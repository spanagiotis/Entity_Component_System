#pragma once
#include <SFML/Graphics.hpp>
#include "BaseComponent.hpp"

namespace TextJustification
{
	enum TextJustification
	{
		TopLeft,
		CenterLeft,
		BottomLeft,
		CenterTop,
		CenterMiddle,
		CenterBottom,
		TopRight,
		CenterRight,
		BottomRight
	};
};

class TextComponent: public BaseComponent
{
public:
	TextComponent(void);
	TextComponent(std::string fontName, int fontsize, sf::Color fontColor, std::string string);
	~TextComponent(void);
	void SetFontSize(int size);
	void SetFontFace(std::string name);
	void SetTextString(std::string text);
	void SetOriginalColor(sf::Color color);
	void SetCurrentColor(sf::Color color);
	void SetJustification(TextJustification::TextJustification);
	void SetPosition(sf::Vector2f position); 
	sf::Color GetOriginalColor(void) const;
	sf::Color GetCurrentColor(void) const;
	sf::Text* GetTextString(void) const;
	sf::FloatRect GetGlobalBounds(void) const;
	sf::FloatRect GetLocalBounds(void) const;
	TextJustification::TextJustification GetJustification(void) const;

private:
	sf::Color originalColor;
	sf::Font font;
	sf::Text* text;
	TextJustification::TextJustification justification;
};