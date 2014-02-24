#pragma once

namespace ComponentBitMasks
{
	enum ComponentBitMasks
	{
		None = 0,
		Position2DComponent = 1,
		TextComponent = 2,
		Render2DComponent = 4,
		BoxColliderComponent = 8,
		MouseOverComponent = 16,
		MouseOverImageComponent = 32,
		SpriteComponent = 64,
		ChangeColorOnMouseOver = 128,
		MouseClickComponent = 256,
		ChangeColorOnMousePress = 512,
		MousePressImageComponent = 1024,
		ControllerComponent = 2048,
		WalkComponent = 4096,
		RunComponent = 8192,
		JumpComponent = 16384,
		DuckComponent = 32768,
		AbilityComponent = 65536,
		SpeedComponent = 131072,
		VelocityComponent = 262144,
		InputComponent = 524288,
	};
};

class BaseComponent
{

public:
	BaseComponent(void);
	~BaseComponent(void);
	int GetBitMask(void) const;

protected:
	int bitMask;
};