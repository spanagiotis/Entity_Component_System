#pragma once
#include <memory>
#include <vector>
#include "Entity.hpp"

class BaseSystem
{
public:
	BaseSystem(void);
	~BaseSystem(void);
	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);
	virtual void ProcessComponents(void) = 0;
	int GetBitMask(void) const;

protected:
	int bitMask;
	std::vector<Entity*> entities;
};