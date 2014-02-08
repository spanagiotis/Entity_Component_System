#pragma once
#include "Entity.hpp"

/// Constructs an entity.
///
/// The entity is just a collection of components and a bitmask easily
/// showing what components are attached to the entity without needing to
/// do any find component lookups.
///
/// @param std::string A name for the entity.
/// @return None
Entity::Entity(std::string name)
{
	this->name  = name;
	bitMask = 0;
}

/// Destructs an entity.
///
/// The entity will automatically delete all its attached components from memory,
/// freeing the user from worrying about keeping track of them. The user should do
/// no manual memory management when it comes to the components. 
///
/// @param std::string A name for the entity.
/// @return None
Entity::~Entity(void)
{
	for(int i =0; i < components.size(); i++)
	{
		delete components[i];
	}
	components.clear();
}

std::string Entity::GetName(void) const
{
	return name;
}

/// Returns a bitmask.
///
/// The bitmask is an OR'd or AND'd list of ComponentBitMasks::. 
///
/// @param None
/// @return std::string A name for the entity.
int Entity::GetBitMask(void) const
{
	return bitMask;
}

/// Quickly tests to see if a specific component bitmask is associated with this entity..
///
/// @param int A ComponentBitMasks:: enum.
/// @return None
bool Entity::HasComponent(int mask)
{
	if((bitMask & mask) == mask)
		return true;
	return false;
}

/// Associates a new component with this entity.
///
/// A pointer to a component is added to the entities collection of components and
/// its bitMask OR'd to reflect the newly added component. Components SHOULD be added like in the example below
/// E.G  someEntity->AttachComponent( new SomeComponent(someParam1, someParam2, ...));
/// This will keep the user from having to worry about a pointer reference as the entity will already take
/// care of the component pointers.
///
/// @param BaseComponent* A pointer to a component that derives from BaseComponent.
/// @return std::string A name for the entity.
void Entity::AttachComponent(BaseComponent* component)
{
	this->components.push_back(component);
	this->bitMask = this->bitMask | component->GetBitMask();
}

/// Returns a pointer to a component in the collection.
///
/// Will return a pointer to the component as long as the components mask type
/// matches the specified mask.
///
/// @param int A ComponetBitMask:: .
/// @return BaseComponent* A pointer to a component.
BaseComponent* Entity::GetComponent(int mask)
{
	if(!HasComponent(mask))
		return NULL;

	for(int i=0; i < components.size(); i++)
	{
		if((components[i]->GetBitMask() & mask) == mask)
		{
			return components[i];
		}
	}
	return NULL;
}

/// Destroys a single defined component.
///
/// Will remove the specific component from the entities component collection and
/// make sure to AND'd the ComponentBitMask:: enum from the entities bitMask variable.
///
/// @param int A ComponetBitMask::
/// @return None
void Entity::RemoveComponent(int mask)
{
	if(!HasComponent(mask))
		return;

	this->bitMask &= mask;

	int position = -1;
	for(unsigned int i = 0; i < components.size(); i++)
	{
		if((components[i]->GetBitMask() & mask) == mask)
		{
			position = i;
			break;
		}
	}

	if(position != -1)
	{
		delete components.at(position);
		components.erase(components.begin() + position);
	}
}

