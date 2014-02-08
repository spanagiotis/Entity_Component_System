#pragma once
#include "World.hpp"

/// Constructs the world.
///
/// The world keeps track of all the entities and systems runnings. 
/// It also takes care of updating all the systems in the proper order
/// in which they were added.
///
/// @param None
/// @return None
World::World(void)
{

}

/// Destructs the world.
///
/// Clears all the appropriate lists of their contents. Will also take 
/// care of deleting all system pointers as entities will delete their own components.
///
/// @param None
/// @return None
World::~World(void)
{
	newEntities.clear();
	entities.clear();

	for(unsigned int i=0; i < systems.size(); i++)
		delete systems[i];

	systems.clear();
}

/// Created a new entity on the heap.
///
/// Will create an empty entity and assign it a name (used for housekeeping purposes).
/// This entity is then added to the newly created entities list and its pointer passed
/// back to the user. The user does not have to worry about deleting this pointer.
///
/// @param std::string A name for the entity.
/// @return Entity* A pointer to the newly created entity.
Entity* World::CreateEntity(std::string name)
{
	Entity* entity = new Entity(name);
	newEntities.push_back(entity);
	return entity;
}

/// Destroys a single defined entity.
///
/// Will remove the specific entity from both the entities list and delete it from
/// memory automatically.
///
/// @param Entity* A pointer to the newly created entity.
/// @return None
void World::RemoveEntity(Entity* entity)
{
	int position = -1;
	for(unsigned int i=0; i < entities.size(); i++)
	{
		if(entities[i] == entity)
			position = i;
	}

	if(position != -1)
	{
		delete entity;
		entities.erase(entities.begin() + position);
	}
}

/// Runs all attached systems.
///
/// Will first update all systems with their new entities and then will being
/// calling all the system update methods.
///
/// @param float Current frame time.
/// @return None
void World::Update(float frameTime)
{
	UpdateSystemsWithNewEntities();
	UpdateSystems();
}


/////////////////////////////////////////////////
// Private
////////////////////////////////////////////////


/// Add new entities to their appropriate systems.
///
/// Any entity created this frame will be passed out to all the systems
/// whose component makeup bitmask they match. This allows the systems to only
/// worry about a small batch of entities and not the entire pot.
///
/// @param None
/// @return None
void World::UpdateSystemsWithNewEntities(void)
{
	if(newEntities.size() > 0)
	{
		for(unsigned int i = 0; i < newEntities.size(); i++)
		{
			for(unsigned int j =0; j < systems.size(); j++)
			{
				if((newEntities[i]->GetBitMask() & systems[j]->GetBitMask()) == systems[j]->GetBitMask())
				{
					systems[j]->AddEntity(newEntities[i]);
					entities.push_back(newEntities[i]);
				}
			}
		}
		newEntities.clear();
	}
}

/// Runs all attached systems.
///
/// Each system will have a chance to process any entities it may have stored.
/// All systems will be called regardless if they have appropriate entities or not.
///
/// @param None
/// @return None
void World::UpdateSystems(void)
{
	for(unsigned int i = 0; i < systems.size(); i++)
	{
		systems[i]->ProcessComponents();
	}
}

/// Add a pointer to a newly created system on the heap.
///
/// @param BaseSystem* A pointer to a system on the heap.
/// @return None
void World::AddSystem(BaseSystem* system)
{
	systems.push_back(system);
}