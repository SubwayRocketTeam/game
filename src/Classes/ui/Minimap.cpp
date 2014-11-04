#include "pch.h"
#include "Minimap.h"

#include "common/resource.h"

#include "objects/Ally.h"
#include "objects/Stage.h"
#include "objects/Unit.h"

using namespace cocos2d;

static Minimap *instance = nullptr;

Minimap *Minimap::create(){
	instance = new Minimap();

	if(instance && instance->init()){
		instance->autorelease();
		return instance;
	}

	CC_SAFE_DELETE(instance);
	return nullptr;
}
Minimap *Minimap::getInstance(){
	return instance;
}

bool Minimap::init(){
	if(!Sprite::initWithFile(R::Minimap))
		return false;

	auto size = getContentSize();

	drawnode = DrawNode::create();
	drawnode->setPosition(
		size.width/2, size.height/2);
	addChild(drawnode);

	enableMouseInput(this);
	scheduleUpdate();

	return true;
}
void Minimap::update(
	float dt){

	drawnode->clear();

	auto size = getContentSize();
	auto players = Ally::getInstance(
		Ally::Type::allyPlayer);
	auto enemies = Ally::getInstance(
		Ally::Type::allyEnemy);
	auto stageSize = Stage::getInstance(0)->getContentSize();
	Vec2 ratio(
		size.width / stageSize.width ,
		size.height / stageSize.height);

	for(auto player : *players){
		auto pos = player->getPosition();
		pos.set(pos.x * ratio.x,
			pos.y * ratio.y);

		drawnode->drawPoint(
			pos, 10, Color4F::GREEN);
	}
	for(auto enemy : *enemies){
		auto pos = enemy->getPosition();
		pos.set(pos.x * ratio.x,
			pos.y * ratio.y);

		drawnode->drawSolidCircle(
			pos, 5, 360,32,  Color4F::RED);
	}
}

void Minimap::onMouseMove(
	int btn, float x,float y){

	auto box = getBoundingBox();

	if(box.containsPoint(Vec2(x,y)))
		setOpacity(128);
	else
		setOpacity(255);
}