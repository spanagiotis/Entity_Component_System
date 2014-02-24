#pragma once
#include <windows.h>
#include "BaseSystem.hpp"
#include "InputComponent.hpp"

class InputSystem : public BaseSystem
{
public:
	InputSystem(sf::RenderWindow* window);
	~InputSystem(void);
	void Process(float elapsedTime);
	void RecieveMessage(MessageInfo* messageInfO);

private:
	void PollEvents(float elapsedTime);
	void OnKeyDown(WPARAM key, float elapsedTime);
	void OnKeyUp(WPARAM key, float elapsedTime);
	void OnLeftButtonDown(WPARAM key, float elapsedTime);
	void OnLeftButtonUp(WPARAM key, float elapsedTime);
	void OnRightButtonDown(WPARAM key, float elapsedTime);
	void OnRightButtonUp(WPARAM key, float elapsedTime);
	void AddKeyToHistory(InputComponent* inputComponent, Key key);
	int maximumKeyHistory;
	sf::RenderWindow* window;
	Key keyState;
	Mouse mouseState;
};