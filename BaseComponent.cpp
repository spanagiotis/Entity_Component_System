#pragma once
#include "BaseComponent.hpp"

BaseComponent::BaseComponent(void)
{

}

BaseComponent::~BaseComponent(void)
{

}

/// Returns the component type via a bitmask.
///
/// @param None
/// @return int - Bitmask.
int BaseComponent::GetBitMask(void) const
{
	return bitMask;
}



