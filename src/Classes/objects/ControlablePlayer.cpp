#include "pch.h"
#include "ControlablePlayer.h"

#include "GlobalResource.h"

#include "Stage.h"
#include "CollisionDetector.h"

#include "shared/JsonLoader.h"

#include "ui/cursor.h"

#include "common/resource.h"

#include "skill/PassiveSkill.h"
#include "skill/ActiveSkill.h"
#include "skill/SkillPool.h"
#include "skill/id.h"
#include "skill/AttributeName.h"

#include "network/Network.h"

using namespace std;
using namespace cocos2d;

static ControlablePlayer *instance = nullptr;

ControlablePlayer::ControlablePlayer(){

	allyID = Ally::Type::allyPlayer;
}
ControlablePlayer::~ControlablePlayer(){
}

ControlablePlayer *ControlablePlayer::create(
	const string &dataPath){

	CC_ASSERT(instance == nullptr);

	instance = new ControlablePlayer();
	
	if(instance && instance->init(dataPath)){
		instance->autorelease();
		return instance;
	}
	CC_SAFE_DELETE(instance);
	return nullptr;
}
ControlablePlayer *ControlablePlayer::getInstance(){
//	CC_ASSERT(instance != nullptr);

	return instance;
}

bool ControlablePlayer::init(
	const string &dataPath){

	if (!Player::init(dataPath))
		return false;

	enableMouseInput(this);
	enableKeyboardInput(this);

	schedule(
		SEL_SCHEDULE(&ControlablePlayer::updateRotation), 0.1f);

	return true;
}

void ControlablePlayer::onExit() {
	disableMouseInput();
	disableKeyboardInput();
	instance = nullptr;

	auto stage = Stage::getInstance(stageID);
	stage->setObserverMode();

	GlobalResource::getInstance()->trash = 0;
	ShowCursor(true);

	Player::onExit();
}


bool ControlablePlayer::useSkill(
	SKillIndex index,
	float x,float y){

	auto skill = skills[index];
	float cooltime = skill->cooltime;

	if(cooltimes[index] > 0.0f)
		return false;
	if (skill->cost > _ATTR(mp))
		return false;

	skill->use(this, Vec2(x,y));

	cooltimes[index] = cooltime;
	_ATTR_VALUE(mp) -= skill->cost;
	stiff = skill->duration;

	auto network = Network::getInstance();
	network->sendUseSkill(
		skill->id, x,y);

	return true;
}

void ControlablePlayer::updateRotation(
	float dt){

	auto network = Network::getInstance();
	network->sendSyncRotation(
		getRotation());
}

void ControlablePlayer::processRotation(
	float x,float y){

	auto worldPos =
		getParent()->convertToWorldSpace(getPosition());
	auto half = worldPos / 2;
	
	double dx = worldPos.x - x;
	double dy = worldPos.y - y;
	double rad = atan2(dy, dx);
	double degree = (rad*180)/M_PI;

	setRotation(-degree + 90);
}

void ControlablePlayer::processMove(
	EventKeyboard::KeyCode keycode){

	if(stiff > 0.0f) return;
	if(moveCounter >= 2) return;

	Vec2 moveBy(0, 0);
	float speed = _ATTR(speed);

	if(moveSwitchVertical == 0){
		if(keycode == EventKeyboard::KeyCode::KEY_W)
			moveBy.set(0, speed), moveSwitchVertical = 1;
		else if(keycode == EventKeyboard::KeyCode::KEY_S)
			moveBy.set(0, -speed), moveSwitchVertical = 1;
	}
	if(moveSwitchHorizontal == 0){
		if(keycode == EventKeyboard::KeyCode::KEY_A)
			moveBy.set(-speed, 0), moveSwitchHorizontal = 1;
		else if(keycode == EventKeyboard::KeyCode::KEY_D)
			moveBy.set(speed, 0), moveSwitchHorizontal = 1;
	}

	float frameRate =
		Director::getInstance()->getFrameRate();

	auto norm = moveBy.getNormalized();
	Network::getInstance()
		->sendMove(
			norm.x, norm.y);

	/*
	runAction(
		MoveBy::create(1.0/frameRate, moveBy))
		->setTag(actionMove);
		*/

	moveCounter++;
}

void ControlablePlayer::processAttack(
	int btn, float x,float y){

	Vec2 mouse(x, y);
	mouse -= getParent()->getPosition();

	if(btn == MOUSE_BUTTON_LEFT){
		useSkill(skillMouseLeft, mouse.x, mouse.y);
	}
	else if(btn == MOUSE_BUTTON_RIGHT){
		useSkill(skillMouseRight, mouse.x, mouse.y);
	}
}

void ControlablePlayer::onKeyboardDown(
	EventKeyboard::KeyCode keycode){

	if(keycode == EventKeyboard::KeyCode::KEY_1)
		addPassive(100);
	if (keycode == EventKeyboard::KeyCode::KEY_SPACE)
		addPassive(12);

	if (keycode == EventKeyboard::KeyCode::KEY_2)
		Player::useSkill(13, getPosition());

	bool moved = false;

	if(keycode == EventKeyboard::KeyCode::KEY_W)
		speed += Vec2(0,1), moved = true;
	if(keycode == EventKeyboard::KeyCode::KEY_S)
		speed += Vec2(0,-1), moved = true;
	if(keycode == EventKeyboard::KeyCode::KEY_A)
		speed += Vec2(-1,0), moved = true;
	if(keycode == EventKeyboard::KeyCode::KEY_D)
		speed += Vec2(1,0), moved = true;

	if(moved){
		auto norm = speed.getNormalized();
		Network::getInstance()
			->sendMove(norm.x, norm.y);
		
		velocity = speed * _ATTR(speed);
		moveCounter ++;
		tick = 0;
	}
}
void ControlablePlayer::onKeyboardUp(
	EventKeyboard::KeyCode keycode){

	if (keycode == EventKeyboard::KeyCode::KEY_SPACE)
		removePassive(12);

	bool moved = false;
	if(keycode == EventKeyboard::KeyCode::KEY_W)
		speed -= Vec2(0,1), moved = true;
	if(keycode == EventKeyboard::KeyCode::KEY_S)
		speed -= Vec2(0,-1), moved = true;
	if(keycode == EventKeyboard::KeyCode::KEY_A)
		speed -= Vec2(-1,0), moved = true;
	if(keycode == EventKeyboard::KeyCode::KEY_D)
		speed -= Vec2(1,0), moved = true;

	if(moved){
		moveCounter --;
		velocity = speed * _ATTR(speed);

		if(moveCounter == 0){
			Network::getInstance()
				->sendMove(0.f, 0.f);
		}
		else{
			auto norm = speed.getNormalized();
			Network::getInstance()
				->sendMove(norm.x, norm.y);
		}
	}
}
void ControlablePlayer::onKeyboardPressed(
	EventKeyboard::KeyCode keycode){

	processRotation(cursor.x,cursor.y);
}

void ControlablePlayer::onMouseMove(
	int btn, float x,float y){

	processRotation(x,y);

	cursor.set(x,y);
}
void ControlablePlayer::onMouseDown(
	int btn, float x,float y){
}
void ControlablePlayer::onMouseUp(
	int btn, float x,float y){
}
void ControlablePlayer::onMousePressed(
	int btn, float x,float y){

	processAttack(btn, x, y);
}