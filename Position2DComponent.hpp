#pragma once
#include <SFML/Graphics.hpp>
#include "BaseComponent.hpp"

class Position2DComponent: public BaseComponent
{
public:
	Position2DComponent(void);
	Position2DComponent(float x, float y);
	~Position2DComponent(void);
	void SetPosition(float x, float y);
	sf::Vector2f GetPosition(void) const;

private:
	sf::Vector2f position;

};