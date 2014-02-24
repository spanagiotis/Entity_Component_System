#pragma once
#include <SFML/Graphics.hpp>
#include "BaseComponent.hpp"

class ChangeColorOnMousePressComponent : public BaseComponent
{
public:
	ChangeColorOnMousePressComponent(void);
	ChangeColorOnMousePressComponent(sf::Color color);
	~ChangeColorOnMousePressComponent(void);
	void SetColor(sf::Color color);
	sf::Color GetColor(void) const;

public:
	sf::Color color;

};