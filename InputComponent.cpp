#include "InputComponent.hpp"

InputComponent::InputComponent(void)
{
	bitMask = ComponentBitMasks::InputComponent;
}

InputComponent::~InputComponent(void)
{

}

bool InputComponent::IsMouseOver(sf::FloatRect bounds, Mouse mouseInfo, MouseOverStates::MouseOverStates& mouseOverState)
{
	if(bounds.contains(mouseInfo.mousePosition.x, mouseInfo.mousePosition.y))
	{
		switch(mouseOverState)
		{
		case MouseOverStates::None:
			{
				mouseOverState = MouseOverStates::In;
			}break;
		case MouseOverStates::In:
			{
				mouseOverState = MouseOverStates::Over;
			}break;
		}
		return true;
	}
	else
	{
		switch(mouseOverState)
		{
		case MouseOverStates::In:
			{
				mouseOverState = MouseOverStates::Out;
			}break;
		case MouseOverStates::Over:
			{
				mouseOverState = MouseOverStates::Out;
			}break;
		case MouseOverStates::Out:
			{
				mouseOverState = MouseOverStates::None;
			}break;
		}
		return false;
	}
}

void InputComponent::SetCurrentKey(Key key)
{
	currentKeyState = key;
}

void InputComponent::SetPreviousKey(Key key)
{
	previousKeyState = key;
}

void InputComponent::SetCurrentMouse(Mouse mouse)
{
	currentMouseState = mouse;
}

void InputComponent::SetPreviousMouse(Mouse mouse)
{
	previousMouseState = mouse;
}

Key InputComponent::GetCurrentKey(void) const
{
	return currentKeyState;
}

Key InputComponent::GetPreviousKey(void) const
{
	return previousKeyState;
}

Mouse InputComponent::GetCurrentMouse(void) const
{
	return currentMouseState;
}

Mouse InputComponent::GetPreviousMouse(void) const
{
	return previousMouseState;
}

int InputComponent::GetKeyHistoryCount(void) const
{
	return keyHistory.size();
}

void InputComponent::AddToKeyHistory(Key key)
{
	keyHistory.push_back(key);
}

void InputComponent::ClearKeyHistory(void)
{
	keyHistory.clear();
}
