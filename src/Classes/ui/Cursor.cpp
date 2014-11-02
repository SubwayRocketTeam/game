#include "pch.h"
#include "Cursor.h"

#include "objects/Player.h"

Cursor* Cursor::instance = nullptr;

Cursor::Cursor() {

}

Cursor::~Cursor() {

}

Cursor* Cursor::create() {
	Cursor* cursor = new Cursor();

	if (cursor && cursor->init()) {
		cursor->autorelease();
		return cursor;
	}
	else {
		delete cursor;
		cursor = nullptr;
		return cursor;
	}
}
bool Cursor::init(){
	enableMouseInput(this);

	return true;
}

Cursor* Cursor::getInstance() {
	return getInstance("");
}

Cursor* Cursor::getInstance(const char* filename) {
	if (!instance) {
		instance = Cursor::create();
	}
	instance->initWithFile(filename);
	return instance;
}

void Cursor::update(float dt) {
	
}

void Cursor::onMouseMove(
	int btn, float x,float y){

	auto player = Player::getInstance();
	auto playerWorldPos = player->getParent()->convertToWorldSpace(
		player->getPosition());

	double dx = playerWorldPos.x - x;
	double dy = playerWorldPos.y - y;
	double rad = atan2(dy, dx);
	double degree = (rad*180)/M_PI;

	setRotation(-degree);
	setPosition(x,y);
}