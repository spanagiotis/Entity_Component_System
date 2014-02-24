#pragma once
#include "FontManager.hpp"
#include "FileNotFoundException.hpp"

std::map<std::string, sf::Font> FontManager::fonts;

void FontManager::LoadFontFile(std::string name)
{
	sf::Font font;
	std::string path = FONT_PATH;
	if(font.loadFromFile(path + name))
	{
		std::cout  << "Successfully loaded font " << (path+name) << std::endl;
		int index = name.find(".");
		std::string fontName = name.substr(0, index);
		fonts.insert(std::make_pair(fontName, font));
	}
	else
	{
		std::cout  << "Font " << (path+name) << " was unable to be loaded." << (path+name) << std::endl;
	}
}

sf::Font FontManager::GetFont(std::string name)
{
	std::map<std::string, sf::Font>::iterator iter;
	iter = fonts.find(name);
	if(iter != fonts.end())
		return iter->second;

	return sf::Font();
}