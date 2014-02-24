#pragma once
#include "BaseSystem.hpp"

class TextButtonSystem : public BaseSystem
{
public:
	TextButtonSystem(void);
	~TextButtonSystem(void);
	void Process(float elapsedTime);
	void RecieveMessage(MessageInfo* messageInfo);
	void OnPressed(void);

};