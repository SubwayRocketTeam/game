#include "pch.h"
#include "Network.h"

#include "ui/ChatBox.h"

void Network::handleChatNoti(
	ChatNoti *pkt){

	auto chatbox = ChatBox::getInstance();
	chatbox->output(pkt->msg);
}