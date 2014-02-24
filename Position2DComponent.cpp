#pragma once
#include "Position2DComponent.hpp"

Position2DComponent::Position2DComponent(void)
{
	bitMask = ComponentBitMasks::Position2DComponent;
}

Position2DComponent::Position2DComponent(float x, float y)
{
	bitMask = ComponentBitMasks::Position2DComponent;
	SetPosition(x, y);
}

Position2DComponent::~Position2DComponent(void)
{

}

void Position2DComponent::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

sf::Vector2f Position2DComponent::GetPosition(void) const
{
	return position;
}