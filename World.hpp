#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Entity.hpp"
#include "BaseSystem.hpp"

class World
{
public:
	World(void);
	~World(void);
	Entity* CreateEntity(std::string name);
	void RemoveEntity(Entity* entity);
	void UpdateLogic(float frameTime);
	void UpdateRenders(float frameTime);
	void UpdateSystemsWithNewEntities(void);
	void AddLogicSystem(BaseSystem* system);
	void AddRenderSystem(BaseSystem* system);

private:
	std::vector<Entity*> newEntities;
	std::vector<Entity*> entities;
	std::vector<BaseSystem*> logicSystems;
	std::vector<BaseSystem*> renderSystems;
};