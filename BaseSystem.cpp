#pragma once
#include "BaseSystem.hpp"

BaseSystem::BaseSystem(void)
{

}

BaseSystem::~BaseSystem(void)
{
	entities.clear();
}

void BaseSystem::AddEntity(Entity* entity)
{
	entities.push_back(entity);
}

void BaseSystem::RemoveEntity(Entity* entity)
{
	int position = -1;
	for(unsigned int i = 0; i < entities.size(); i++)
	{
		if(entities[i] == entity)
		{
			position = i;
		}
	}

	if(position != -1)
		entities.erase(entities.begin() + position);
}

int BaseSystem::GetBitMask(void) const
{
	return bitMask;
}
