#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <map>
#include <string>
#include <ctime>
#include <iomanip>

#include <boost\function.hpp>
#include <boost\any.hpp>
#include <SFML/Graphics.hpp>

#include "World.hpp"
#include "Entity.hpp"
#include "FontManager.hpp"

#include "Position2DComponent.hpp"
#include "TextComponent.hpp"
#include "BoxColliderComponent.hpp"
#include "ChangeColorOnMouseOverComponent.hpp"
#include "ChangeColorOnMousePressComponent.hpp"
#include "MouseOverComponent.hpp"
#include "MouseClickComponent.hpp"
#include "InputComponent.hpp"

#include "RenderTextSystem.hpp"
#include "TextButtonSystem.hpp"
#include "InputSystem.hpp"

int main(int argc, char *argv[])
{
	std::cout << "Initializing audio system..." << std::endl;

	std::cout << "Loading fonts..." << std::endl;
	FontManager::LoadFontFile("arial.ttf");
	FontManager::LoadFontFile("NHLMONTR.TTF");
	std::cout << "Fonts Loaded." << std::endl;

	std::cout << "Creating window..." << std::endl;
	sf::RenderWindow* windowMain;
	windowMain = new sf::RenderWindow;
	windowMain->create(sf::VideoMode(1280, 720), "Lightyear");

	std::cout << "Initializing ECS world manager and systems." << std::endl;
	World* world = new World();
	RenderTextSystem* renderTextSystem = new RenderTextSystem(windowMain);
	TextButtonSystem* textButtonSystem = new TextButtonSystem();
	InputSystem* inputSystem = new InputSystem(windowMain);

	std::cout << "Adding systems to world..." << std::endl;
	world->AddLogicSystem(inputSystem);
	world->AddLogicSystem(textButtonSystem);
	world->AddRenderSystem(renderTextSystem);

	std::cout << "Creating test object - Text Based Button..." << std::endl;
	// Entity Start - Create a text based button.
	Entity* testTextButton = world->CreateEntity("Test Text Button");
	testTextButton->AttachComponent(new InputComponent());
	TextComponent* textComponent = new TextComponent("arial", 28, sf::Color::Magenta, "0");
	testTextButton->AttachComponent(textComponent);
	testTextButton->AttachComponent(new Position2DComponent(200.0f,windowMain->getSize().y/2));
	testTextButton->AttachComponent(new MouseOverComponent());
	testTextButton->AttachComponent(new ChangeColorOnMouseOverComponent(sf::Color::Yellow));
	testTextButton->AttachComponent(new BoxColliderComponent(textComponent->GetLocalBounds().width, textComponent->GetLocalBounds().height));
	testTextButton->AttachComponent(new MouseClickComponent(MouseButton::Left));
	testTextButton->AttachComponent(new ChangeColorOnMousePressComponent(sf::Color::Red));
	BaseComponent* bc = testTextButton->GetComponent(ComponentBitMasks::MouseClickComponent);
	MouseClickComponent* mouseClickComponent = static_cast<MouseClickComponent*>(bc);
	mouseClickComponent->AddLeftClickAction(std::bind(&TextButtonSystem::Emit, textButtonSystem, MessageType::CHANGE_TEXT, "I have changed."));
	// Entity end

	// Attach methods to the message center
	std::function<void(MessageInfo*)> changeTextMethod = std::bind(&RenderTextSystem::ChangeText, renderTextSystem, std::placeholders::_1);
	MessageCenter::Subscribe(MessageType::CHANGE_TEXT, boost::function<void(MessageInfo*)>(changeTextMethod));

	// Add listners(an entity) to a system
	textButtonSystem->AddListener(MessageType::CHANGE_TEXT, testTextButton);

	std::cout <<"Starting fps counter (currently broken)..." << std::endl;
	sf::Font fpsFont = FontManager::GetFont("arial");
	sf::Text fpsLabel("0", fpsFont, 12);
	fpsLabel.setPosition(10,10);
	fpsLabel.setColor(sf::Color::White);
	int frameCount = 0;
	float framesPerSecond = 0;
	sf::Clock clock;
	double time = 0.0;
	const double deltaTime = 0.1;
	double accumulator = 0.0;
	double previousState = 0.0;
	double currentState = 0.0;
	double maxFrameTime = 0.25;
	double currentTime = std::clock();

	std::cout <<"Starting game loop..." << std::endl;
	while(windowMain->isOpen())
	{
		double newTime = std::clock();
		double frameTime = newTime - currentTime;
		if(frameTime > maxFrameTime)
			frameTime = maxFrameTime;

		currentTime = newTime;
		accumulator += frameTime;

		while(accumulator >= deltaTime)
		{
			previousState = currentState;
			world->UpdateLogic((float)deltaTime);
			time += deltaTime;
			accumulator -= deltaTime;
		}

		const double alpha = accumulator / deltaTime;
		double newState = currentState * alpha + previousState * (1.0 - alpha);
		world->UpdateRenders(deltaTime);
		windowMain->draw(fpsLabel);
		windowMain->display();
		world->UpdateSystemsWithNewEntities();
		windowMain->clear();
	}

	std::cout << "Cleaning up and ending game..." << std::endl;
	return 0;
}
