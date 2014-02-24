#pragma once
#include <memory>
#include <vector>
#include <map>
#include "Entity.hpp"
#include "MessageInfo.hpp"
#include "MessageCenter.hpp"

class BaseSystem
{
public:
	BaseSystem(void);
	~BaseSystem(void);
	virtual void Process(float elapsedTime) = 0;
	virtual void RecieveMessage(MessageInfo* messageInfo) = 0;
	int GetBitMask(void) const;
	void AddEntity(Entity* entity);
	void AddListener(MessageType::MessageType messageType, Entity* entity);
	void RemoveListener(Entity* entity);
	void Emit(MessageType::MessageType, boost::any params);

protected:
	int bitMask;
	std::vector<Entity*> entities;

private:
	std::multimap<MessageType::MessageType, Entity*> listeners;
};