#pragma once
#include <SFML/Graphics.hpp>
#include "BaseSystem.hpp"

class RenderTextSystem : public BaseSystem
{
public:
	RenderTextSystem(sf::RenderWindow* windowMain);
	~RenderTextSystem(void);
	void Process(float elapsedTime);
	void ChangeText(MessageInfo* messageInfo);
	void RecieveMessage(MessageInfo* messageInfo);

private:
	sf::RenderWindow* windowMain;

};