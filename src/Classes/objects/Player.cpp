#include "pch.h"
#include "Player.h"

#include "Bullet.h"
#include "Trash.h"
#include "TrashPool.h"
#include "PlayerGauge.h"
#include "EffectFactory.h"
#include "Effect.h"
#include "EnemyFactory.h"
#include "GlobalResource.h"

#include "Stage.h"
#include "CollisionDetector.h"

#include "ui/cursor.h"
#include "ui/gauge.h"
#include "ui/UserResources.h"
#include "ui/StatusConsole.h"
#include "ui/SkillIconPanel.h"

#include "common/resource.h"
#include "common/PhysicsFactory.h"
#include "common/JsonLoader.h"

#include "skill/PassiveSkill.h"
#include "skill/ActiveSkill.h"
#include "skill/SkillPool.h"
#include "skill/id.h"
#include "skill/AttributeName.h"

using namespace std;
using namespace cocos2d;

static Player *instance = nullptr;

Player::Player() : 
	moveCounter(0), moveSwitchVertical(0), moveSwitchHorizontal(0),
	speedFactor(1),
	exp(0), expLimit(60 * 1), level(0),
	immortal(0), stiff(0){

	allyID = Ally::Type::allyPlayer;
}
Player::~Player(){
}

Player *Player::create(
	const string &dataPath){

	CC_ASSERT(instance == nullptr);

	instance = new Player();
	
	if(instance && instance->init(dataPath)){
		instance->autorelease();
		return instance;
	}
	CC_SAFE_DELETE(instance);
	return nullptr;
}
Player *Player::getInstance(){
	CC_ASSERT(instance != nullptr);

	return instance;
}

bool Player::init(
	const string &dataPath){

	if (!Unit::init(R::PlayerBody))
		return false;
	if(!initExternalData(dataPath))
		return false;

	enableMouseInput(this);
	enableKeyboardInput(this);

	auto gauge = PlayerGauge::create(
		_ATTR(hp), _ATTR_MAX(hp));
	gauge->setPosition(getContentSize()/2);
	addChild(gauge, -1);

	scheduleUpdate();

	return true;
}
bool Player::initAttrs(){
	Unit::initAttrs();

	return true;
}
bool Player::initPhysics(){
	Stage::getInstance(0)->getCollisionDetector()->addUnit(this);
	radius = 30;
	return true;
	/*
	auto factory = PhysicsFactory::getInstance();
	auto pbody = factory->make("player");

	if(pbody){
		pbody->setAngularDamping(100);
		pbody->setLinearDamping(100);
		setPhysicsBody(pbody);
		return true;
	}
	
	return false;
	*/
}
bool Player::initExternalData(
	const string &dataPath){

	Json::Value root;
	if(!JsonLoader::load(dataPath,root))
		return false;

	/* attr */
	auto attrList = root.get("attrs", Json::Value::null);
	if(attrList.isNull())
		return false;

	for(auto attr : attrList){
		auto name = attr.get("name", "").asString();
		float value = attr.get("value", 0).asFloat();

		attrs[name].set(value);
	}

	/* incr */
	auto incrList = root.get("incrs", Json::Value::null);
	if(incrList.isNull())
		return false;

	/* skill list */
	auto skillList = root.get("skills", Json::Value::null);
	if(skillList.isNull())
		return false;

	auto pool = SkillPool::getInstance();
	for(auto skill : skillList){
		skills.push_back(
			(ActiveSkill*)pool->get(skill.asInt()));
		cooltimes.push_back(0);
	}

	return true;
}

bool Player::useSkill(
	SKillIndex index,
	float x,float y){

	auto skill = skills[index];
	float cooltime = skill->cooltime;

	if(cooltimes[index] > 0.0f)
		return false;
	if (skill->cost > _ATTR(mp))
		return false;
	if(index == skillMouseLeft)
		cooltime *= _ATTR(attackSpeed);

	skill->use(this, Vec2(x,y));

	cooltimes[index] = cooltime;
	_ATTR_VALUE(mp) -= skill->cost;
	stiff = skill->duration;

	/* ui 쿨타임 업데이트 */
	auto panel = SkillIconPanel::getInstance();
	panel->use(skill->id);

	return true;
}

void Player::update(
	float dt){
		
	updateConditions(dt);

	/* TODO : 충돌 범위 상수나 이미지 크기 기반으로 하도록 */
	/* TODO : 빨려들어오는건 쓰레기가 직접 오는데,
	 *        청소하는건 플레이어가 청소
	 *        어떻게 할건지 정하기 */
	auto resource = GlobalResource::getInstance();
	auto pos = getPosition();
	auto trashPool = TrashPool::getInstance();
	auto trashes = trashPool->query(
		Rect(pos.x-10,pos.y-10,20,20));

	for(auto trash : trashes){
		trash->sweep();
		resource->trash += 1;
		__ATTR(gold).increase(1);
	}

	moveCounter = 0;
	moveSwitchHorizontal = moveSwitchVertical = 0;

	auto resources = UserResources::getInstance();
	resources->setExpAndMaxExp(exp, expLimit);
	resources->setGold(_ATTR(gold));
	if (exp >= expLimit) {
		exp = 0;
		expLimit *= 2;
		level++;
		resources->setLevel(level);
	}
}
void Player::updateConditions(
	float dt){

	/* cooltime */
	for(float &cooltime : cooltimes){
		if(cooltime > 0.0f)
			cooltime -= dt;
	}

	/* stiff */
	if(stiff > 0.0f)
		stiff -= dt;

	/* IMMORTAL */
	if(immortal > 0.0f)
		immortal -= dt;
}

bool Player::onDamage(
	const AttackData& attackData){

	if(immortal > 0.0f)
		return false;

	/* TODO : 무적 기간 상수에 집어넣기 */
	blink();
	immortal = 0.5;
	stiff = MAX(stiff, 0.2);

	auto deltaNorm =
		(getPosition() -
		attackData.object->getPosition())
		.getNormalized();

	runAction(
		EaseExponentialOut::create(
			MoveBy::create(0.2, deltaNorm * 70)
		));

	return true;
}
bool Player::onDeath(){
	return false;
}

void Player::processRotation(
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
void Player::processEyeline(
	float x,float y){

	/* disabled */
	/*
	Node *contactObject = nullptr;
	Vec2 contactPoint = Vec2(x,y);
	getPhysicsBody()->getWorld()->rayCast(
		[&](PhysicsWorld &world, const PhysicsRayCastInfo& info, void* data){
			if(info.shape == getPhysicsBody()->getShape(0))
				return true;

			contactPoint = info.contact;
			contactObject = info.shape->getBody()->getNode();
			return false;
		},
		getPosition(), Vec2(x,y),
		nullptr);
		*/
	
		/*
	auto pool = EnemyPool::getInstance();
	if(contactObject){
		pool->focus((Enemy*)contactObject);
	}
	else{
		pool->focus(nullptr);
	}
	*/
}
void Player::processMove(
	EventKeyboard::KeyCode keycode){

	if(stiff > 0.0f) return;
	if(moveCounter >= 2) return;

	Vec2 moveBy(0, 0);
	float speed = _ATTR(speed) * speedFactor;

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

	runAction(
		MoveBy::create(1.0/frameRate, moveBy))
		->setTag(actionMove);

	moveCounter++;
}

void Player::processAttack(
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

void Player::onKeyboardDown(
	EventKeyboard::KeyCode keycode){

	if(keycode == EventKeyboard::KeyCode::KEY_1)
		addPassive(100);

	if (keycode == EventKeyboard::KeyCode::KEY_Z) {
		EnemyFactory::getInstance()->spawn(EnemyType::enemyBasic);
	}
}
void Player::onKeyboardUp(
	EventKeyboard::KeyCode keycode){
}
void Player::onKeyboardPressed(
	EventKeyboard::KeyCode keycode){

	processEyeline(cursor.x, cursor.y);
	processMove(keycode);
	processRotation(cursor.x,cursor.y);
}

void Player::onMouseMove(
	int btn, float x,float y){

	processEyeline(x,y);
	processRotation(x,y);

	cursor.set(x,y);
}
void Player::onMouseDown(
	int btn, float x,float y){

	this->hit();
}
void Player::onMouseUp(
	int btn, float x,float y){
}
void Player::onMousePressed(
	int btn, float x,float y){

	processAttack(btn, x, y);
}