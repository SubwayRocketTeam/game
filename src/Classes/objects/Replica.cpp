#include "pch.h"
#include "Replica.h"

#include "common/resource.h"

using namespace std;
using namespace cocos2d;

Replica::Replica(){
}
Replica::~Replica(){
}

Replica *Replica::create(){
	auto instance = new Replica();
	
	if(instance && instance->init()){
		instance->autorelease();
		return instance;
	}
	CC_SAFE_DELETE(instance);
	return nullptr;
}

bool Replica::init(){
	if (!ControlablePlayer::init("type1.json"))
		return false;

	runAction(
		Sequence::create(
			FadeOut::create(3),
			CallFunc::create([=](){
				disableMouseInput();
			}),
			RemoveSelf::create(),
			nullptr));

	return true;
}

void Replica::onKeyboardDown(
	EventKeyboard::KeyCode keycode){
}
void Replica::onKeyboardUp(
	EventKeyboard::KeyCode keycode){
}
void Replica::onKeyboardPressed(
	EventKeyboard::KeyCode keycode){

	processRotation(cursor.x,cursor.y);
}

void Replica::onMouseMove(
	int btn, float x,float y){

	processRotation(x,y);

	cursor.set(x,y);
}
void Replica::onMousePressed(
	int btn, float x,float y){

	processAttack(btn, x, y);
}