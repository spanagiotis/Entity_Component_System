#pragma once
#include <SFML/Graphics.hpp>
#include "BaseComponent.hpp"

class ChangeColorOnMouseOverComponent : public BaseComponent
{
public:
	ChangeColorOnMouseOverComponent(void);
	ChangeColorOnMouseOverComponent(sf::Color color);
	~ChangeColorOnMouseOverComponent(void);
	void SetColor(sf::Color color);
	sf::Color GetColor(void) const;

private:
	sf::Color color;

};