#pragma once
#include <functional>
#include <boost/any.hpp>
#include "BaseComponent.hpp"
//#include "Input.hpp"
#include "InputComponent.hpp"

class MouseClickComponent : public BaseComponent
{
public:
	MouseClickComponent(int mask);
	~MouseClickComponent(void);
	void SetButtonPressState(PressState::PressState state, MouseButton::MouseButton button, float time);
	bool IsRespondsToButtonPressed(void) const;
	PressState::PressState GetButtonPressState(MouseButton::MouseButton button) const;
	float GetPressTime(void) const;
	int RespondsToButtons(void) const;
	
	void AddLeftClickAction(std::function<void(void)>);
	void AddRightClickAction(std::function<void(void)>);
	void RunLeftClickActionList(void);
	void RunRightClickActionList(void);
private:
	int clickCount;
	int buttonToUseMask;
	PressState::PressState leftButton;
	PressState::PressState rightButton;
	PressState::PressState middleButton;
	std::vector<std::function<void(void)>> leftClickActions;
	std::vector<std::function<void(void)>> rightClickActions;
	float time;

};