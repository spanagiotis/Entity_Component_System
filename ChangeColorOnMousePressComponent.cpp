#pragma once
#include "ChangeColorOnMousePressComponent.hpp"

ChangeColorOnMousePressComponent::ChangeColorOnMousePressComponent(void)
{
	bitMask = ComponentBitMasks::ChangeColorOnMousePress;
}

ChangeColorOnMousePressComponent::ChangeColorOnMousePressComponent(sf::Color color)
{
	bitMask = ComponentBitMasks::ChangeColorOnMousePress;
	SetColor(color);
}

ChangeColorOnMousePressComponent::~ChangeColorOnMousePressComponent(void)
{

}

void ChangeColorOnMousePressComponent::SetColor(sf::Color color)
{
	this->color = color;
}

sf::Color ChangeColorOnMousePressComponent::GetColor(void) const
{
	return color;
}