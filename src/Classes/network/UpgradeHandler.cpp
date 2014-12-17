#include "pch.h"
#include "Network.h"

#include "objects/Unit.h"
#include "objects/ControlablePlayer.h"
#include "objects/GlobalResource.h"
#include "ui/UpgradeBar.h"

using namespace cocos2d;

void Network::handleUpgrade(
	UpgradeNoti *pkt){

	static std::string attrs[] = { "", Attr::hp, Attr::attack, Attr::speed, Attr::range };
	auto unit = Unit::getInstanceByID(
		pkt->id);

	if (!unit)
		return;

	Player* player = (Player*)unit;
	player->upgrade(attrs[pkt->upgrade_type]);

	if (player == ControlablePlayer::getInstance()) {
		auto upgradeBar = UpgradeBar::getInstance();
		upgradeBar->upgradeOver();
	}
}
