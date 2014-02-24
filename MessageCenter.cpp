#pragma once
#include "MessageCenter.hpp"

int MessageCenter::index;
std::multimap<MessageType::MessageType, std::function<void(MessageInfo*)>> MessageCenter::messages;


void MessageCenter::Subscribe(MessageType::MessageType messageType, std::function<void(MessageInfo*)> func)
{
	messages.insert(std::make_pair(messageType, func));
}

void MessageCenter::Dispatch(MessageInfo* messageInfo)
{
	std::multimap<MessageType::MessageType, std::function<void(boost::any)>>::iterator it;

	auto msgRange = messages.equal_range(messageInfo->GetMessageType());
	for(auto it = msgRange.first; it != msgRange.second; ++it)
		it->second(messageInfo);
}