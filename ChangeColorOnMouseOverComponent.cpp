#pragma once
#include "ChangeColorOnMouseOverComponent.hpp"

ChangeColorOnMouseOverComponent::ChangeColorOnMouseOverComponent(void)
{
	bitMask = ComponentBitMasks::ChangeColorOnMouseOver;
}

ChangeColorOnMouseOverComponent::ChangeColorOnMouseOverComponent(sf::Color color)
{
	bitMask = ComponentBitMasks::ChangeColorOnMouseOver;
	SetColor(color);
}

ChangeColorOnMouseOverComponent::~ChangeColorOnMouseOverComponent(void)
{

}

void ChangeColorOnMouseOverComponent::SetColor(sf::Color color)
{
	this->color = color;
}

sf::Color ChangeColorOnMouseOverComponent::GetColor(void) const
{
	return color;
}