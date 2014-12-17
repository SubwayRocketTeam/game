#include "pch.h"
#include "Network.h"

#include "objects/Unit.h"
#include "objects/Player.h"

using namespace cocos2d;

void Network::sendUpgrade(
	UpgradeType upgradeType){

	UpgradeRequest pkt;
	pkt.upgrade_type = upgradeType;
	send(pkt);
}
