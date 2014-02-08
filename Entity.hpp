#pragma once
#include <memory>
#include <vector>
#include <string>
#include "BaseComponent.hpp"

class Entity
{

public:
	Entity(std::string name);
	~Entity(void);
	std::string GetName(void) const;
	int GetBitMask(void) const;
	bool HasComponent(int mask);
	void AttachComponent(BaseComponent* component);
	BaseComponent* GetComponent(int mask);
	void RemoveComponent(int mask);

private:
	std::string name;
	int bitMask;
	std::vector<BaseComponent*> components;

};

