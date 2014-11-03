#include "pch.h"
#include "Cursor.h"

#include "objects/Player.h"
#include "common/resource.h"

static Cursor *instance = nullptr;

Cursor::Cursor() {
}
Cursor::~Cursor() {
}

Cursor* Cursor::create() {
	instance = new Cursor();

	if (instance && instance->init()) {
		instance->autorelease();
		return instance;
	}
	CC_SAFE_DELETE(instance);
	return nullptr;
}
Cursor* Cursor::getInstance() {
	return instance;
}

bool Cursor::init(){
	if(!Sprite::initWithFile(R::Cursor))
		return false;

	enableMouseInput(this);
	scheduleUpdate();

	return true;
}

void Cursor::update(
	float dt){

	processRotation(mouse.x, mouse.y);
}
void Cursor::onMouseMove(
	int btn, float x,float y){

	mouse.set(x,y);
}
void Cursor::processRotation(
	float x,float y){
	
	auto player = Player::getInstance();
	auto playerWorldPos = player->getParent()->convertToWorldSpace(
		player->getPosition());

	double dx = playerWorldPos.x - x;
	double dy = playerWorldPos.y - y;
	double rad = atan2(dy, dx);
	double degree = (rad*180)/M_PI;

	setRotation(-degree - 45);
	setPosition(x,y);
}