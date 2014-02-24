#pragma once
#include "TextButtonSystem.hpp"
#include "TextComponent.hpp"
#include "ChangeColorOnMouseOverComponent.hpp"
#include "ChangeColorOnMousePressComponent.hpp"
#include "MouseOverComponent.hpp"
#include "BoxColliderComponent.hpp"
#include "Position2DComponent.hpp"
#include "MouseClickComponent.hpp"
#include "InputComponent.hpp"
#include "MessageInfo.hpp"
#include "MessageCenter.hpp"

TextButtonSystem::TextButtonSystem(void)
{
	bitMask = ComponentBitMasks::Position2DComponent |
		ComponentBitMasks::TextComponent |
		ComponentBitMasks::MouseOverComponent |
		ComponentBitMasks::ChangeColorOnMouseOver |  
		ComponentBitMasks::ChangeColorOnMousePress |
		ComponentBitMasks::BoxColliderComponent |
		ComponentBitMasks::MouseClickComponent |
		ComponentBitMasks::InputComponent;
}


TextButtonSystem::~TextButtonSystem(void)
{

}

void TextButtonSystem::Process(float elapsedTime)
{
	for(unsigned int i = 0; i < entities.size(); i++)
	{
		if((bitMask & entities[i]->GetBitMask()) == bitMask)
		{
			MouseOverComponent* mouseOverComponent;
			ChangeColorOnMouseOverComponent* changeColorOnMouseOverComponent;
			ChangeColorOnMousePressComponent* changeColorOnMousePressComponent;
			TextComponent* textComponent;
			BoxColliderComponent* boxColliderComponent;
			Position2DComponent* position2DComponent;
			MouseClickComponent* mouseClickComponent;
			InputComponent* inputComponent;

			mouseOverComponent = static_cast<MouseOverComponent*>(entities[i]->GetComponent(ComponentBitMasks::MouseOverComponent));
			changeColorOnMouseOverComponent = static_cast<ChangeColorOnMouseOverComponent*>(entities[i]->GetComponent(ComponentBitMasks::ChangeColorOnMouseOver));
			changeColorOnMousePressComponent = static_cast<ChangeColorOnMousePressComponent*>(entities[i]->GetComponent(ComponentBitMasks::ChangeColorOnMousePress));
			textComponent = static_cast<TextComponent*>(entities[i]->GetComponent(ComponentBitMasks::TextComponent));
			boxColliderComponent = static_cast<BoxColliderComponent*>(entities[i]->GetComponent(ComponentBitMasks::BoxColliderComponent));
			position2DComponent = static_cast<Position2DComponent*>(entities[i]->GetComponent(ComponentBitMasks::Position2DComponent));
			mouseClickComponent = static_cast<MouseClickComponent*>(entities[i]->GetComponent(ComponentBitMasks::MouseClickComponent));
			inputComponent = static_cast<InputComponent*>(entities[i]->GetComponent(ComponentBitMasks::InputComponent));



			Mouse mouseInfo = inputComponent->GetCurrentMouse();
			sf::FloatRect rect(position2DComponent->GetPosition().x,
				position2DComponent->GetPosition().y + textComponent->GetLocalBounds().top, 
				boxColliderComponent->GetBounds().x,
				boxColliderComponent->GetBounds().y);

			MouseOverStates::MouseOverStates state = mouseOverComponent->GetState();
			bool isMouseOver = inputComponent->IsMouseOver(rect,mouseInfo, state);
			mouseOverComponent->SetState(state);

			if(isMouseOver)
			{
				if(state == MouseOverStates::In)
				{
					textComponent->SetCurrentColor(changeColorOnMouseOverComponent->GetColor());
				}

				if(((mouseClickComponent->RespondsToButtons() & MouseButton::Left) == MouseButton::Left) && mouseInfo.button == MouseButton::Left)
				{
					if(mouseInfo.state == PressState::Pressed)
					{
						textComponent->SetCurrentColor(changeColorOnMousePressComponent->GetColor());
					}
					else if(mouseInfo.state == PressState::Held)
					{
						textComponent->SetCurrentColor(changeColorOnMousePressComponent->GetColor());
					}
					else if(mouseInfo.state == PressState::Released)
					{
						mouseClickComponent->RunLeftClickActionList();
						textComponent->SetCurrentColor(changeColorOnMouseOverComponent->GetColor());
					}
				}
				else if(((mouseClickComponent->RespondsToButtons() & MouseButton::Right) == MouseButton::Right) && mouseInfo.button == MouseButton::Right)
				{
					if(mouseInfo.state == PressState::Pressed)
					{ 
						textComponent->SetCurrentColor(changeColorOnMousePressComponent->GetColor());
					}
					else if(mouseInfo.state == PressState::Held)
					{
						textComponent->SetCurrentColor(changeColorOnMousePressComponent->GetColor());
					}
					else if(mouseInfo.state == PressState::Released)
					{
						textComponent->SetCurrentColor(changeColorOnMouseOverComponent->GetColor());
						//Execute right click action list
					}
				}	
			}
			else
			{
				if(state == MouseOverStates::None)
				{
					textComponent->SetCurrentColor(textComponent->GetOriginalColor());
				}
			}
		}
	}
}

void TextButtonSystem::RecieveMessage(MessageInfo* messageInfo)
{

}

void TextButtonSystem::OnPressed(void)
{

}