#pragma once
#include "BaseSystem.hpp"
#include <vector>

BaseSystem::BaseSystem(void)
{

}

BaseSystem::~BaseSystem(void)
{
	entities.clear();
}

/// Returns the components this system must have.
///
/// Returns a bitmask containing the components that must be attached to an entity
/// for this system to pay attention to it.
///
/// @param None
/// @return int bitmask.
int BaseSystem::GetBitMask(void) const
{
	return bitMask;
}

/// Adds the entity to a list of entities that it will loop through each process().
///
/// @param Entity* - Pointer to an entity.
/// @return None
void BaseSystem::AddEntity(Entity* entity)
{
	entities.push_back(entity);
}

/// Adds an entity that will listen for messages caused by this system.
///
/// @param MessageType - The enum type for the message.
/// @param Entity* - Pointer to an entity.
/// @return None
void BaseSystem::AddListener(MessageType::MessageType messageType, Entity* entity)
{
	listeners.insert(std::make_pair(messageType, entity));
}

/// Removes any listening entities.
///
/// Since an entity can be attached to multiple message types the function first finds all the matching entity
/// iterators and then loops through and erases those elements from the multimap.
///
/// @param Entity* - Pointer to an entity.
/// @return None
void BaseSystem::RemoveListener(Entity* entity)
{
	std::map<MessageType::MessageType, Entity*>::iterator it;
	std::vector<std::map<MessageType::MessageType, Entity*>::iterator> iterators;

	// Find all matching entities
	for (it = listeners.begin(); it != listeners.end(); ++it )
	{
		if (it->second == entity)
		{
			iterators.push_back(listeners.find(it->first));
		}
	}

	// Remove them
	for(int i =0; i < iterators.size(); i++)
	{
		listeners.erase(iterators[i]);
	}
}

/// Notifies the message center with a specific message.
///
/// Each system has the ability to emit a message directly to the message center. The emit method only
/// cares about the MessageInfo* argument.
///
/// @param MessageType - The enum type for the message.
/// @param boost::any - Any number of parameters that are needed by the specific message type to be properly parsed.
/// @return None
void BaseSystem::Emit(MessageType::MessageType messageType, boost::any params)
{		
	std::multimap<MessageType::MessageType, boost::any>::iterator it;

	auto msgRange = listeners.equal_range(messageType);
	for(auto it = msgRange.first; it != msgRange.second; ++it)
		MessageCenter::Dispatch(new MessageInfo(messageType, it->second, params));
}
