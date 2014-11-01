#include "Stage.h"

#include "objects/Player.h"
#include "objects/EnemySpawner.h"
#include "common/resource.h"

#include "common/JsonLoader.h"

using namespace std;
using namespace cocos2d;

Stage::Stage(){
}
Stage::~Stage(){
}

Stage *Stage::create(){
	Stage *p = new Stage();
	
	if(p && p->init()){
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
}

bool Stage::init(){
	if (!Node::init())
		return false;

	if(!initExternalData())
		return false;


	floor = Sprite::create(R::StageFloor);
	addChild(floor, -1);

	enableMouseInput(this);
	scheduleUpdate();

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
	else if(name == "light")
		node = Node::create(); /* replace me */
	else if(name == "shop")
		node = Node::create(); /* replace me */
	else{
		cocos2d::log("unknown object");
		return false;
	}

	node->setPosition(x,y);
	addChild(node);

	return true;
}

void Stage::update(
	float dt){

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto floorSize = floor->getContentSize();
	auto player = Player::getInstance();

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

void Stage::onMouseMove(
	int btn, float x,float y){

	mousePos.set(x,y);
}