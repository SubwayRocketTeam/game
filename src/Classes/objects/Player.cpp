#include "pch.h"
#include "Player.h"

#include "EnemyPool.h"
#include "Bullet.h"

#include "AnimationPool.h"

#include "ui/cursor.h"
#include "ui/gauge.h"
#include "ui/UserResources.h"
#include "ui/StatusConsole.h"

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
	exp(0), expLimit(60 * 1), gold(0), level(0){
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

DrawNode* drawNode;

bool Player::init(
	const string &dataPath){

	if (!Unit::init(R::PlayerBody, BodyParts))
		return false;
	if(!initExternalData(dataPath))
		return false;

	enableMouseInput(this);
	enableKeyboardInput(this);
	enableDebug();

	lay = DrawNode::create();
	addChild(lay);

	scarf = Scarf::create();
	addChild(scarf);

	hp = Gauge::create(R::HPGauge, static_cast<PartedBody*>(body)->getBodyWidth(), 100);
	hp->setRegenPerSec(10);

	addChild(hp);
	hp->setPositionX(-static_cast<PartedBody*>(body)->getBodyWidth() / 2);
	hp->setPositionY(static_cast<PartedBody*>(body)->getOriginY() + static_cast<PartedBody*>(body)->getBodyHeight() + hp->getContentSize().height);

	mp = Gauge::create(R::MPGauge, static_cast<PartedBody*>(body)->getBodyWidth(), 100);
	addChild(mp);
	mp->setPositionX(-static_cast<PartedBody*>(body)->getBodyWidth() / 2);
	mp->setPositionY(static_cast<PartedBody*>(body)->getOriginY() + static_cast<PartedBody*>(body)->getBodyHeight());

	hp->reduceGauge(50);

	drawNode = DrawNode::create();
	drawNode->drawCircle(Vec2::ZERO, 100, 0, 32, false, Color4F::RED);
	drawNode->drawLine(Vec2(-100, 0), Vec2(100, 0), Color4F::RED);
	addChild(drawNode);

	scheduleUpdate();

	return true;
}
bool Player::initPhysics(){
	auto factory = PhysicsFactory::getInstance();
	auto pbody = factory->make("player");

	if(pbody){
		pbody->setAngularDamping(100);
		pbody->setLinearDamping(100);
		setPhysicsBody(pbody);
		return true;
	}
	
	return false;
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

	if(cooltimes[index] > 0.0f)
		return false;
	if(skill->cost > attrs["mp"].get())
		return false;
	
	skill->use(this, Vec2(x,y));

	cooltimes[index] = skill->cooltime;
	attrs["mp"].getValue() -= skill->cost;
	stiff = skill->duration;

	return true;
}

void Player::update(
	float dt){
		
	updateConditions(dt);

	moveCounter = 0;
	moveSwitchHorizontal = moveSwitchVertical = 0;

	exp++;
	gold++;

	auto resources = UserResources::getInstance();
	resources->setExpAndMaxExp(exp, expLimit);
	resources->setGold(gold);
	if (exp >= expLimit) {
		exp = 0;
		expLimit *= 2;
		level++;
		resources->setLevel(level);
	}

	lay->clear();
	for (int i = 0; i < 10; i++) {
		lay->drawDot((this->convertToNodeSpace(cursor) - Vec2(0, 0)).getNormalized() * i * 50, 5, Color4F::RED);
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

	body->setRotation(-degree + 90);
	scarf->pushRotation(degree + 90);
	drawNode->setRotation(-degree + 90);

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

	runAction(
		MoveBy::create(1.0/frameRate, moveBy))
		->setTag(actionMove);

	body->runAnimation(
		AnimationPool::getInstance()
		->getBodyAnimation(R::Run)
		, true);

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

	processAttack(btn, x,y);
}
void Player::onMouseUp(
	int btn, float x,float y){
}