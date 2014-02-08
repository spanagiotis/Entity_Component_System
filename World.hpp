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
	void Update(float frameTime);
	void AddSystem(BaseSystem* system);

private:
	void UpdateSystemsWithNewEntities(void);
	void UpdateSystems(void);
	std::vector<Entity*> newEntities;
	std::vector<Entity*> entities;
	std::vector<BaseSystem*> systems;


};