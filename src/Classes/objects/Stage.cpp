#include "pch.h"
#include "Stage.h"

#include "shared/JsonLoader.h"

#include "common/resource.h"

#include "objects/ControlablePlayer.h"
#include "objects/EnemySpawner.h"
#include "objects/CollisionDetector.h"

#include "scene/ResultScene.h"

using namespace std;
using namespace cocos2d;

static Stage *instances[2] =
	{nullptr, nullptr};

Stage::Stage(){
}
Stage::~Stage(){
}

bool Stage::create(){
	for(int i=0;i<_countof(instances);i++){
		instances[i] = new Stage();

		if(instances[i] && instances[i]->init(i)){
			instances[i]->autorelease();
		}
		else{
			CC_SAFE_DELETE(instances[i]);
			return false;
		}
	}

	return true;
}
Stage *Stage::getInstance(
	int id){

	switch(id){
	case 0:
		return instances[0];
	case 1:
		return instances[1];
	default:
		cocos2d::log("unknown stage id");
		return nullptr;
	}
}

CollisionDetector* Stage::getCollisionDetector(){
	return collisionDetector;
}


bool Stage::init(
	int _id){

	if (!Node::init())
		return false;

	if(!initExternalData())
		return false;

	id = _id;

	floor = Sprite::create(R::StageFloor);
	addChild(floor, -1);

	enableMouseInput(this);
	scheduleUpdate();

	setContentSize(floor->getContentSize());

	collisionDetector = CollisionDetector::create();
	addChild(collisionDetector);

	return true;
}
bool Stage::initExternalData(){
	Json::Value root;
	Json::Value objects;

	if(!JsonLoader::load(R::StageJson, root))
		return false;

	/* map id */
	id = root.get("id", -1).asInt();
	if(id == -1)
		return false;
	
	/* object array */
	objects = root.get("objects", -1);
	if(objects == -1)
		return false;
	/* each object */
	for(auto object : objects){
		string name =
			object.get("id", string::npos).asString();
		int x = object.get("x", 0).asInt();
		int y = object.get("y", 0).asInt();
		
		if(!initObject(name, x,y))
			return false;
	}

	return true;
}
bool Stage::initObject(
	const string &name,
	int x,int y){

	Node *node = nullptr;

	if(name == "spawn"){
		node = EnemySpawner::create();
	}
	else{
		cocos2d::log("unknown object");
		return false;
	}

	node->setPosition(x,y);
	addChild(node);

	return true;
}

void Stage::setObserverMode(){
	auto windowSize = Director::getInstance()->getVisibleSize();
	auto size = getContentSize();

	runAction(
		Sequence::create(
			DelayTime::create(1.f),
			Spawn::create(
				MoveTo::create(1.f, windowSize / 2),
				ScaleTo::create(1.f, windowSize.width / size.width, windowSize.height / size.height),
				nullptr),
			nullptr
		));
}

void Stage::gameOver() {
	auto size = Director::getInstance()->getVisibleSize();
	auto sprite = Sprite::create(R::GameOver);
	sprite->setPosition(size / 2);
	getParent()->addChild(sprite, Z::Popup);
	runAction(
		Sequence::create(
		DelayTime::create(5.f),
		CallFunc::create([]{Director::getInstance()->replaceScene(ResultScene::scene());}),
		nullptr
		)
		);
}

void Stage::update(
	float dt){

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto floorSize = floor->getContentSize();
	auto player = ControlablePlayer::getInstance();
	
	if (player) {
		/* 자기가 속한 스테이지만 카메라 이동 */
		if(player->getStageID() != id)
			return;

		auto center =
			player->getPosition() + (mousePos - visibleSize/2) / 2;

		center.x =
			MIN(floorSize.width - visibleSize.width/2,
				MAX(visibleSize.width/2, center.x + floorSize.width / 2)) - floorSize.width / 2;
		center.y =
			MIN(floorSize.height - visibleSize.height/2,
				MAX(visibleSize.height/2, center.y + floorSize.height / 2)) - floorSize.height / 2;

		setPosition((Vec2)visibleSize/2 - center);
	}
}

void Stage::onMouseMove(
	int btn, float x,float y){

	mousePos.set(x,y);
}

void Stage::onExit() {
	disableMouseInput();
	Node::onExit();
}
