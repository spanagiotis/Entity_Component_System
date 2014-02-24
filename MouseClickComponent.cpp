#pragma once
#include "MouseClickComponent.hpp"
//#include "Input.hpp"

MouseClickComponent::MouseClickComponent(int buttonToUseMask)
{
	bitMask = ComponentBitMasks::MouseClickComponent;
	leftButton = PressState::None;
	rightButton = PressState::None;
	middleButton= PressState::None;
	time = 0.0f;
	this->buttonToUseMask = buttonToUseMask;
}

MouseClickComponent::~MouseClickComponent(void)
{

}

void MouseClickComponent::SetButtonPressState(PressState::PressState state, MouseButton::MouseButton button, float time)
{
	this->time = time;
	switch(button)
	{
	case MouseButton::Left:
		{
			leftButton = state;
		}break;
	case MouseButton::Right:
		{
			rightButton = state;
		}break;
	case MouseButton::Middle:
		{
			middleButton = state;
		}break;
	}
}

bool MouseClickComponent::IsRespondsToButtonPressed(void) const
{
	if((MouseButton::Left & buttonToUseMask) == buttonToUseMask)
	{
		if(leftButton == PressState::Pressed)
			return true;
	}

	if((MouseButton::Right & buttonToUseMask) == buttonToUseMask)
	{
		if(rightButton == PressState::Pressed)
			return true;
	}

	if((MouseButton::Middle & buttonToUseMask) == buttonToUseMask)
	{
		if(middleButton == PressState::Pressed)
			return true;
	}

	return false;
}

PressState::PressState MouseClickComponent::GetButtonPressState(MouseButton::MouseButton button) const
{
	switch(button)
	{
	case MouseButton::Left:
		{
			return leftButton;
		}break;
	case MouseButton::Right:
		{
			return rightButton;
		}break;
	case MouseButton::Middle:
		{
			return middleButton;
		}break;
	default:
		{

		}break;
	}
}

float MouseClickComponent::GetPressTime(void) const
{
	return time;
}

int MouseClickComponent::RespondsToButtons(void) const
{
	return buttonToUseMask;
}

void MouseClickComponent::AddLeftClickAction(std::function<void(void)> action)
{
	leftClickActions.push_back(action);
}

void MouseClickComponent::AddRightClickAction(std::function<void(void)> action)
{
	rightClickActions.push_back(action);
}

void MouseClickComponent::RunLeftClickActionList(void)
{
	clickCount++;
	for(unsigned int i =0; i < leftClickActions.size(); i++)
	{
		leftClickActions[i]();
	}
}

void MouseClickComponent::RunRightClickActionList(void)
{
	clickCount++;
	for(unsigned int i =0; i < leftClickActions.size(); i++)
	{
		rightClickActions[i]();
	}
}