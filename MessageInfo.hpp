#pragma once
#include <boost/any.hpp>
#include "Entity.hpp"

namespace MessageType
{
	enum MessageType
	{
		CHANGE_TEXT = 0,
		CHANGE_TEXT_COLOR,
		TAKE_SHIELD_DAMAGE,
		TAKE_SUBSYSTEM_DAMAGE,
		TAKE_HULL_DAMAGE,
		TAKE_HEALTH_DAMAGE
	};
};

class MessageInfo
{
public:
	MessageInfo(MessageType::MessageType messageType, Entity* listenEntity, boost::any params);
	~MessageInfo(void);
	MessageType::MessageType GetMessageType(void);
	Entity* GetListener(void);
	boost::any GetParams(void);

private:
	MessageType::MessageType messageType;
	Entity* listener;
	boost::any params;
};