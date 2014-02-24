#pragma once
#include <tuple>
#include "RenderTextSystem.hpp"
#include "TextComponent.hpp"
#include "Position2DComponent.hpp"

RenderTextSystem::RenderTextSystem(sf::RenderWindow* windowMain)
{
	this->windowMain = windowMain;
	bitMask = ComponentBitMasks::TextComponent | ComponentBitMasks::Position2DComponent; 
}

RenderTextSystem::~RenderTextSystem(void)
{

}

void RenderTextSystem::Process(float elapsedTime)
{
	for(unsigned int i =0; i < entities.size(); i++)
	{
		// Render the text
		if((entities[i]->GetBitMask() & bitMask) == bitMask)
		{
			TextComponent* textComponent = static_cast<TextComponent*>(entities[i]->GetComponent(ComponentBitMasks::TextComponent));
			Position2DComponent* position2DComponent = static_cast<Position2DComponent*>(entities[i]->GetComponent(ComponentBitMasks::Position2DComponent));
			textComponent->SetPosition(position2DComponent->GetPosition());
			windowMain->draw((*textComponent->GetTextString()));
		}
	}
}


void RenderTextSystem::ChangeText(MessageInfo* messageInfo)
{
	boost::any params = messageInfo->GetParams();
	const char* c = typeid(params.type()).name();
	if(params.type() == typeid(const char*))
	{
		auto param = boost::any_cast<const char*>(params);
		if(!messageInfo->GetListener()->HasComponent(ComponentBitMasks::TextComponent))
			return;

		TextComponent* textComponent = static_cast<TextComponent*>(messageInfo->GetListener()->GetComponent(ComponentBitMasks::TextComponent));
		textComponent->SetTextString(param);
		delete messageInfo;
	}
}

void RenderTextSystem::RecieveMessage(MessageInfo* messageInfo)
{
	
}