#pragma once
#include <vector>
#include <map>
#include <functional>
#include <boost\any.hpp>
#include "BaseSystem.hpp"
#include "MessageInfo.hpp"

class MessageCenter
{
public:
	~MessageCenter(void) { };
	static void Subscribe(MessageType::MessageType messageType, std::function<void(MessageInfo*)> params);
	static void Dispatch(MessageInfo* messageInfo);

private:
	MessageCenter(void) { };
	static int index;
	static std::multimap<MessageType::MessageType, std::function<void(MessageInfo*)>> messages;

};