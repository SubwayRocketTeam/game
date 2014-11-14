#include "pch.h"
#include "PartedBody.h"
#include "BodyAnimation.h"

using namespace std;
using namespace cocos2d;

PartedBody::PartedBody() :
	partNum(0),
	body(MaxParts), bodyOriginal(MaxParts),
	runningAnimation(MaxParts){
}
PartedBody::~PartedBody(){
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
	const string &imageName, const int part){

	CCASSERT(part >= 0, "part는 0보다 크거나 같아야 함.");

	if (!Sprite::init())
		return false;

	partNum = part;

	char path[256];
	if (partNum == 0) {
		partNum = 1;
		sprintf(path, "%s.png",
			imageName.c_str());
		if (!makeBodyPart(path, 0)) return false;
	}
	else {
		for (int i = 0; i<partNum; i++) {
			sprintf(path, "%s_%d.png",
				imageName.c_str(), i + 1);
			if (!makeBodyPart(path, i)) return false;
		}
	}

	schedule(
		SEL_SCHEDULE(&PartedBody::updateCharacter),
		1.0 / 60);

	return true;
}

bool PartedBody::makeBodyPart(const std::string partName, const int partId)
{
	body[partId] = Sprite::create(partName);

	if (body[partId] == nullptr)
		return false;
	bodyOriginal[partId] = body[partId]->getSpriteFrame();
	addChild(body[partId], -partId);
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


void PartedBody::runAnimation(BodyAnimation* const animation, bool repeatForever)
{
	CCASSERT(animation, "nullptr이 애니메이션으로 들어옴.");

	for (int i = 1; i <= partNum; ++i)
	{
		Animation* partAnim = animation->getPartAnimation(i);
		if (!partAnim) continue;
		else if (partAnim == runningAnimation[i - 1]) continue;
		else stopAnimation(i);

		Action* action;

		if (repeatForever)
		{
			action = RepeatForever::create(Animate::create(partAnim));
		}
		else
		{
			action = Sequence::create(
				Animate::create(partAnim),
				CallFunc::create(CC_CALLBACK_0(PartedBody::stopAnimation, this, i)),
				NULL);
		}

		body[i - 1]->runAction(action);

		runningAnimation[i - 1] = partAnim;
	}
}

void PartedBody::stopAnimation(const int id)
{
	CCASSERT(id > 0 && id <= partNum, "정지하는 애니메이션 id가 범위 밖");

	if (runningAnimation[id - 1])
	{
		body[id - 1]->stopAllActions();
		body[id - 1]->setSpriteFrame(bodyOriginal[id - 1]);
		runningAnimation[id - 1] = nullptr;
	}
}

float PartedBody::getOriginY() {
	auto vec1 = convertToWorldSpace(body[0]->boundingBox().origin);
	auto vec2 = convertToWorldSpace(body[MaxParts-1]->getBoundingBox().origin);

	return min(vec1.y, vec2.y);
}

float PartedBody::getBodyHeight() {
	Rect rect1 = body[0]->getBoundingBox();
	Rect rect2 = body[MaxParts - 1]->getBoundingBox();
	auto vec1 = convertToWorldSpace(rect1.origin);
	auto vec2 = convertToWorldSpace(rect2.origin);

	return max(vec1.y + rect1.size.height, vec2.y + rect2.size.height) - getOriginY();
}

float PartedBody::getBodyWidth() {
	return body[0]->getBoundingBox().size.width;
}

void PartedBody::stopAllAnimation()
{
	for (int i = 0; i <= partNum; ++i)
		stopAnimation(i);
}

vector<Sprite*>::iterator PartedBody::begin(){
	return body.begin();
}
vector<Sprite*>::iterator PartedBody::end(){
	return body.end();
}
