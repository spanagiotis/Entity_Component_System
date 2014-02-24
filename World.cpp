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

	for(unsigned int i=0; i < logicSystems.size(); i++)
		delete logicSystems[i];

	for(unsigned int i=0; i < renderSystems.size(); i++)
		delete renderSystems[i];

	logicSystems.clear();
	renderSystems.clear();
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

/// Runs systems which control game logic (movement, interaction, input, etc).
///
/// Will update all systems with their new entities and then will call all the
///system update methods.
///
/// @param float Current frame time.
/// @return None
void World::UpdateLogic(float frameTime)
{
	for(unsigned int i = 0; i < logicSystems.size(); i++)
	{
		logicSystems[i]->Process(frameTime);
	}
}

/// Runs systems which control object rendering (sprites, textures, 3d models, etc).
///
/// Will update all systems with their new entities and then will call all the
///system update methods.
///
/// @param float Current frame time.
/// @return None
void World::UpdateRenders(float frameTime)
{
	for(unsigned int i = 0; i < renderSystems.size(); i++)
	{
		renderSystems[i]->Process(frameTime);
	}
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
			for(unsigned int j =0; j < logicSystems.size(); j++)
			{
				if((newEntities[i]->GetBitMask() & logicSystems[j]->GetBitMask()) == logicSystems[j]->GetBitMask())
				{
					logicSystems[j]->AddEntity(newEntities[i]);
					entities.push_back(newEntities[i]);
				}
			}

			for(unsigned int j =0; j < renderSystems.size(); j++)
			{
				if((newEntities[i]->GetBitMask() & renderSystems[j]->GetBitMask()) == renderSystems[j]->GetBitMask())
				{
					renderSystems[j]->AddEntity(newEntities[i]);
					entities.push_back(newEntities[i]);
				}
			}
		}
		newEntities.clear();
	}
}

/// Add a pointer to a newly created logic based system on the heap.
///
/// @param BaseSystem* A pointer to a system on the heap.
/// @return None
void World::AddLogicSystem(BaseSystem* system)
{
	logicSystems.push_back(system);
}

/// Add a pointer to a newly created render based system on the heap.
///
/// @param BaseSystem* A pointer to a system on the heap.
/// @return None
void World::AddRenderSystem(BaseSystem* system)
{
	renderSystems.push_back(system);
}