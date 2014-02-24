#pragma once

#include <iostream>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>

#define FONT_PATH "Fonts/";

class FontManager
{
public:
	~FontManager(void) { };
	static void LoadFontFile(std::string);
	static sf::Font FontManager::GetFont(std::string name);

private:
	FontManager(void) { };
	static std::map<std::string,sf::Font> fonts;
};