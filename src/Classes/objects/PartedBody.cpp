#include "pch.h"
#include "PartedBody.h"
#include "BodyAnimation.h"

using namespace std;
using namespace cocos2d;

PartedBody::PartedBody() :partNum(0){
	ZeroMemory(body, sizeof(body));
	ZeroMemory(bodyTexture, sizeof(bodyTexture));
	ZeroMemory(runningAnimation, sizeof(runningAnimation));
}
PartedBody::~PartedBody(){
}

PartedBody *PartedBody::create(
	const string &filename){

	PartedBody *u = new PartedBody();

	if(u && u->init(filename)){
		u->autorelease();
		return u;
	}
	CC_SAFE_DELETE(u);
	return nullptr;
}

PartedBody *PartedBody::create(
	const string &prefix, const int part){

	PartedBody *u = new PartedBody();

	if (u && u->init(prefix, part)){
		u->autorelease();
		return u;
	}
	CC_SAFE_DELETE(u);
	return nullptr;
}

bool PartedBody::init(
	const string &filename){

	if(!Sprite::init())
		return false;

	partNum = 1;

	char path[256];
	sprintf(path, "%s.png",
		filename.c_str());

	body[0] = Sprite::create(path);

	if (body[0] == nullptr)
		return false;
	bodyTexture[0] = body[0]->getTexture();
	addChild(body[0], 0);

	schedule(
		SEL_SCHEDULE(&PartedBody::updateCharacter),
		1.0/60);

	return true;
}

bool PartedBody::init(
	const string &prefix, const int part){

	if (!Sprite::init())
		return false;

	partNum = part;

	for (int i = 0; i<partNum; i++){
		char path[256];
		sprintf(path, "%s_%d.png",
			prefix.c_str(), i + 1);

		body[i] = Sprite::create(path);

		if (body[i] == nullptr)
			return false;
		bodyTexture[i] = body[i]->getTexture();
		addChild(body[i], -i);
	}

	schedule(
		SEL_SCHEDULE(&PartedBody::updateCharacter),
		1.0 / 60);

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

	for (int i = 0; i < partNum; i++) {
		body[i]->setPosition(
			delta * ratio * (partNum - i));
	}
}

float PartedBody::getRotation() const{
	return body[0]->getRotation();
}
void PartedBody::setRotation(
	float angle){

	for (int i = 0; i < partNum; i++) {
		body[i]->setRotation(angle);
	}
}

Vec2 PartedBody::getHeadPosition(){
	return body[0]->getPosition();
}


void PartedBody::runAnimation(BodyAnimation* const animation)
{
	CCASSERT(animation, "nullptr이 애니메이션으로 들어옴.");
	for (int i = 1; i <= partNum; ++i)
	{
		Animation* partAnim = animation->getPartAnimation(i);
		if (!partAnim) continue;
		else if (partAnim == runningAnimation[i]) continue;
		else stopAnimation(i);

		body[i]->runAction(Animate::create(partAnim));
	}
}

void PartedBody::stopAnimation(const int id)
{
	CCASSERT(id > 0 && id <= partNum, "정지하는 애니메이션 id가 범위 밖");
	if (runningAnimation[id])
	{
		body[id]->stopAllActions();
		body[id]->setTexture(bodyTexture[id]);
		runningAnimation[id] = nullptr;
	}
}

void PartedBody::stopAllAnimation()
{
	for (int i = 0; i <= partNum; ++i)
		stopAnimation(i);
}
