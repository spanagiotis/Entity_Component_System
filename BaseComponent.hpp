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