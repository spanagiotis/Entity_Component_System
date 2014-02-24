#include "InputSystem.hpp"

InputSystem::InputSystem(sf::RenderWindow* window)
{
	bitMask = ComponentBitMasks::InputComponent;
	this->window = window;
	maximumKeyHistory = 10;
}

InputSystem::~InputSystem(void)
{

}

void InputSystem::Process(float elapsedTime)
{
	PollEvents(elapsedTime);
	for(unsigned int i =0; i < entities.size(); i++)
	{
		// Render the text
		if((entities[i]->GetBitMask() & bitMask) == bitMask)
		{
			InputComponent* inputComponent = static_cast<InputComponent*>(entities[i]->GetComponent(ComponentBitMasks::InputComponent));
			Mouse inputPreviousMouseState = inputComponent->GetPreviousMouse();
			Mouse inputCurrentMouseState = inputComponent->GetCurrentMouse();
			Key inputPreviousKeyState = inputComponent->GetPreviousKey();
			Key inputCurrentKeyState = inputComponent->GetCurrentKey();

			if(inputPreviousMouseState.button == mouseState.button)
			{
				if(inputPreviousMouseState.state == PressState::Pressed)
					mouseState.state = PressState::Held;
			}

			if(inputPreviousMouseState.state == PressState::Released)
			{
				mouseState.button = MouseButton::None;
				mouseState.state = PressState::None;
			}

			inputPreviousMouseState = mouseState;

			if(inputPreviousKeyState.decimal == keyState.decimal && inputPreviousKeyState.state == PressState::Pressed && keyState.state == PressState::Pressed)
			{
				keyState.state = PressState::Held;
				AddKeyToHistory(inputComponent, keyState);
			}
			else if (inputPreviousKeyState.state == PressState::Released && keyState.state == PressState::Released)
			{
				keyState.Reset();
			}
			else
			{
				inputPreviousKeyState = keyState;
			}

			sf::Event event;
			while (window->pollEvent(event))
			{
				if(event.type == sf::Event::Closed)
					window->close();
			}

			mouseState.mousePosition = sf::Mouse::getPosition((*window));
			inputComponent->SetPreviousMouse(inputCurrentMouseState);
			inputComponent->SetPreviousKey(inputCurrentKeyState);
			inputComponent->SetCurrentMouse(mouseState);
			inputComponent->SetCurrentKey(keyState);
		}
	}
}

void InputSystem::RecieveMessage(MessageInfo* messageInfo)
{

}

void InputSystem::PollEvents(float elapsedTime)
{
	MSG msg;
	if (PeekMessage(&msg,0,0,0, PM_NOREMOVE))
	{
		switch(msg.message)
		{
		case WM_KEYDOWN:
			OnKeyDown(msg.wParam, elapsedTime);
			break;
		case WM_KEYUP:
			OnKeyUp(msg.wParam, elapsedTime);
			break;
		case WM_LBUTTONDOWN:
			OnLeftButtonDown(msg.wParam, elapsedTime);
			break;
		case WM_LBUTTONUP:
			OnLeftButtonUp(msg.wParam, elapsedTime);
			break;
		case WM_RBUTTONDOWN:
			OnRightButtonDown(msg.wParam, elapsedTime);
			break;
		case WM_RBUTTONUP:
			OnRightButtonUp(msg.wParam, elapsedTime);
			break;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	sf::Event event;
	while (window->pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
			window->close();
	}
}


// Fires on the WM_KEYDOWN message and sets the keyInfo to a pressed state.
void InputSystem::OnKeyDown(WPARAM key, float elapsedTime)
{
	keyState.decimal = key;
	keyState.symbol= static_cast<char>(key);
	keyState.pressTime = elapsedTime;
	keyState.state = PressState::Pressed;
	//AddToKeyHistory(keyInfo);
}

// Fires on the WM_KEYUP message and sets the keyInfo to a released state.
void InputSystem::OnKeyUp(WPARAM key, float elapsedTime)
{
	keyState.decimal = key;
	keyState.symbol= static_cast<char>(key);
	keyState.pressTime = elapsedTime;
	keyState.state = PressState::Released;
	//AddToKeyHistory(keyInfo);
}

void InputSystem::OnLeftButtonDown(WPARAM key, float elapsedTime)
{
	mouseState.button = MouseButton::Left;
	mouseState.pressTime = elapsedTime;
	mouseState.state = PressState::Pressed;
}

void InputSystem::OnLeftButtonUp(WPARAM key, float elapsedTime)
{
	mouseState.button = MouseButton::Left;
	mouseState.pressTime = elapsedTime;
	mouseState.state = PressState::Released;
}

void InputSystem::OnRightButtonDown(WPARAM key, float elapsedTime)
{
	mouseState.button = MouseButton::Right;
	mouseState.pressTime = elapsedTime;
	mouseState.state = PressState::Pressed;
}

void InputSystem::OnRightButtonUp(WPARAM key, float elapsedTime)
{
	mouseState.button = MouseButton::Right;
	mouseState.pressTime = elapsedTime;
	mouseState.state = PressState::Released;
}

void InputSystem::AddKeyToHistory(InputComponent* inputComponent, Key key)
{
	if(inputComponent->GetKeyHistoryCount() >= maximumKeyHistory)
		inputComponent->ClearKeyHistory();

	inputComponent->AddToKeyHistory(key);
}