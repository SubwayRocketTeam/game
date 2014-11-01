#include "PartedBody.h"

using namespace std;
using namespace cocos2d;

PartedBody::PartedBody(){
}
PartedBody::~PartedBody(){
}

PartedBody *PartedBody::create(
	const string &prefix){

	PartedBody *u = new PartedBody();

	if(u && u->init(prefix)){
		u->autorelease();
		return u;
	}
	CC_SAFE_DELETE(u);
	return nullptr;
}

bool PartedBody::init(
	const string &prefix){

	if(!Sprite::init())
        return false;

	for(int i=0;i<Parts;i++){
		char path[256];
		sprintf(path, "%s_%d.png",
			prefix.c_str(), i+1);

		body[i] = Sprite::create(path);

		if(body[i] == nullptr)
			return false;
		addChild(body[i], -i);
	}

	schedule(
		SEL_SCHEDULE(&PartedBody::updateCharacter),
		1.0/60);

	return true;
}

void PartedBody::updateCharacter(
	float dt){

	static float ratio = 0.03f;
	auto director = Director::getInstance();

	auto visibleSize = director->getVisibleSize();
	auto origin = director->getVisibleOrigin();

	auto localPos = getPosition();
	auto worldPos =
		getParent()->convertToWorldSpace(localPos);
	auto delta = 
		worldPos - (origin + visibleSize)/2;

	for (int i=0;i<Parts;i++){
		body[i]->setPosition(
			delta * ratio * (5-i));
	}
}

float PartedBody::getRotation() const{
	return body[0]->getRotation();
}
void PartedBody::setRotation(
	float angle){

	for(auto part : body){
		part->setRotation(angle);
	}
}