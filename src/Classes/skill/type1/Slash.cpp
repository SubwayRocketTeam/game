#include "pch.h"
#include "Slash.h"

#include "objects/PartedBody.h"
#include "objects/Unit.h"
#include "common/resource.h"

#include "ui/StatusConsole.h"

using namespace std;
using namespace cocos2d;

bool Slash::init(
	const string &dataPath){

	if(!ActiveSkill::init(dataPath))
		return false;

	return true;
}
void Slash::use(
	Unit *u,
	cocos2d::Vec2 pos){

	auto console = StatusConsole::getInstance();
	console->output("use slash");

	auto slash = Sprite::create(R::SkillSlash);

	slash->runAction(
		Sequence::create(
			FadeOut::create(0.4),
			RemoveSelf::create(),
			nullptr));
	slash->setRotation(
		u->getBody()->getRotation());

	u->addChild(slash);
}