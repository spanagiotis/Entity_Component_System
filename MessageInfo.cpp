#include "MessageInfo.hpp"

MessageInfo::MessageInfo(MessageType::MessageType messageType, Entity* listener, boost::any params)
{
	this->messageType = messageType;
	this->listener = listener;
	this->params = params;
}

MessageInfo::~MessageInfo(void)
{

}

MessageType::MessageType MessageInfo::GetMessageType(void)
{
	return messageType;
}

Entity* MessageInfo::GetListener(void)
{
	return listener;
}

boost::any MessageInfo::GetParams(void)
{
	return params;
}