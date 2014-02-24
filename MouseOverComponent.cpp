#pragma once
#include "MouseOverComponent.hpp"
//#include "Input.hpp"
#include <iostream>

MouseOverComponent::MouseOverComponent(void)
{
	bitMask = ComponentBitMasks::MouseOverComponent;
	mouseOverState = MouseOverStates::None;
}

MouseOverComponent::~MouseOverComponent(void)
{

}

void MouseOverComponent::SetState(MouseOverStates::MouseOverStates mouseOverState)
{
	this->mouseOverState = mouseOverState;
}

MouseOverStates::MouseOverStates MouseOverComponent::GetState(void) const
{
	return mouseOverState;
}