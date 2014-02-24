#pragma once
#include <SFML/Graphics.hpp>
#include "BaseComponent.hpp"

class BoxColliderComponent : public BaseComponent
{
public:
	BoxColliderComponent(void);
	BoxColliderComponent(float width, float height);
	~BoxColliderComponent(void);
	void SetBounds(float width, float heigt);
	sf::Vector2f GetBounds(void) const;

private:
	float width;
	float height;
};