#include "Stage.h"

#include "objects/Player.h"
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
	addChild(floor);

	enableMouseInput(this);
	scheduleUpdate();

	return true;
}
bool Stage::initExternalData(){
	Json::Value root;
	Json::Value objects;

	if(!JsonLoader::load(R::StageJson, root))
		return false;

	id = root.get("id", -1).asInt();
	if(id == -1)
		return false;
	
	objects = root.get("objects", -1);
	if(objects == -1)
		return false;

	for(auto object : objects){
		string objectId =
			object.get("id", string::npos).asString();

		printf("%s\n", objectId.c_str());
	}

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