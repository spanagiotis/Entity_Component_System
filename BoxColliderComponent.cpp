#pragma once
#include "BoxColliderComponent.hpp"

BoxColliderComponent::BoxColliderComponent(void)
{
	bitMask = ComponentBitMasks::BoxColliderComponent;
	SetBounds(0.0f,0.0f);
}

BoxColliderComponent::BoxColliderComponent(float width, float height)
{
	bitMask = ComponentBitMasks::BoxColliderComponent;
	SetBounds(width, height);
}

BoxColliderComponent::~BoxColliderComponent(void)
{

}

void BoxColliderComponent::SetBounds(float width, float height)
{
	this->width = width;
	this->height = height;
}

sf::Vector2f BoxColliderComponent::GetBounds(void) const
{
	return sf::Vector2f(width,height);
}
