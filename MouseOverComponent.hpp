#pragma once
#include "BaseComponent.hpp"
//#include "Input.hpp"
#include "InputComponent.hpp"

class MouseOverComponent : public BaseComponent
{
public:
	MouseOverComponent(void);
	~MouseOverComponent(void);
	void SetState(MouseOverStates::MouseOverStates mouseOverState);
	MouseOverStates::MouseOverStates GetState(void) const;

private:
	MouseOverStates::MouseOverStates mouseOverState;

};