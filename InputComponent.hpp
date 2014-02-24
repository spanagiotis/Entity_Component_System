#pragma once
#include "BaseComponent.hpp"
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <windows.h>

namespace PressState
{
	enum PressState
	{
		Pressed = 1,
		Released = 2,
		Held = 4,
		None = 8
	};
}

namespace MouseButton
{
	enum MouseButton
	{
		Left = 1,
		Right = 2,
		Middle = 4,
		None = 8
	};
}

namespace MouseOverStates
{
	enum MouseOverStates
	{
		None = 1,
		In = 2,
		Over = 4,
		Out = 8,
	};
};

struct Key
{
	Key() { Reset(); }
	Key(char s, int d, float pt, PressState::PressState st) : symbol(s), decimal(d), pressTime(pt), state(st) { }
	char symbol;
	int decimal;
	float pressTime;
	PressState::PressState state;
	bool SameKey(char rhsKey) { if(symbol == rhsKey) return true; return false; }
	void Reset() { symbol = char(0); decimal = 0; pressTime = 0.0f; state = PressState::None; } 
};

struct Mouse
{
	Mouse() { Reset(); }
	Mouse(MouseButton::MouseButton b, float pt) : button(b), pressTime(pt) { }
	MouseButton::MouseButton button;
	float pressTime;
	PressState::PressState state;
	sf::Vector2i mousePosition;
	void Reset() { button = MouseButton::None; pressTime = 0.0f; state=PressState::None; }
};

class InputComponent : public BaseComponent
{
public:
	InputComponent(void);
	~InputComponent(void);
	bool IsMouseOver(sf::FloatRect bounds, Mouse mouseInfo, MouseOverStates::MouseOverStates& mouseOverState);
	void SetCurrentKey(Key key);
	void SetPreviousKey(Key key);
	void SetCurrentMouse(Mouse mouse);
	void SetPreviousMouse(Mouse mouse);
	Key GetCurrentKey(void) const;
	Key GetPreviousKey(void) const;
	Mouse GetCurrentMouse(void) const;
	Mouse GetPreviousMouse(void) const;
	int GetKeyHistoryCount(void) const;
	void AddToKeyHistory(Key key);
	void ClearKeyHistory(void);

private:
	Key previousKeyState;
	Key currentKeyState;
	Mouse previousMouseState;
	Mouse currentMouseState;
	std::list<Key> keyHistory;

};