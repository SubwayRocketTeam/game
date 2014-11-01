#include "Scarf.h"

using namespace std;
using namespace cocos2d;

Scarf::Scarf(){
}
Scarf::~Scarf(){
}

Scarf *Scarf::create(){
	Scarf *u = new Scarf();

	if(u && u->init()){
		u->autorelease();
		return u;
	}
	CC_SAFE_DELETE(u);
	return nullptr;
}

bool Scarf::init(){
	if(!DrawNode::init())
        return false;

	for (int i=0;i<Segments;i++){
		scarfNode[i].point = Vec2(i*Length, 0);
		scarfNode[i].tail = Vec2(1, 0);
	}

	scheduleUpdate();
	return true;
}

void Scarf::update(
	float dt){

	static float t = 0;
	t += dt*8;

	Vec2 pos = getParent()->getPosition();
	Vec2 u = Vec2(0,1);
	
	u.rotate(Vec2::ZERO,
		CC_DEGREES_TO_RADIANS(angle));

	Vec2 startDirection = -u;
	startDirection.rotate(Vec2::ZERO, std::sin(t)*0.25);

	for (int i=Segments-1;i>0;--i){
		scarfNode[i].point += scarfNode[i].velocity[Delay - 1];
		scarfNode[i].point += (scarfNode[i - 1].tail - scarfNode[i].tail) * (Length * i);

		for (int j=Delay-1;j>0;--j){
			scarfNode[i].velocity[j] = scarfNode[i].velocity[j - 1];
		}

		scarfNode[i].velocity[0] = scarfNode[i - 1].velocity[Delay - 1];
		scarfNode[i].tail = scarfNode[i - 1].tail;
	}

	for(int j=Delay-1;j>0;--j){
		scarfNode[0].velocity[j] = scarfNode[0].velocity[j - 1];
	}

	scarfNode[0].velocity[0] = pos - scarfNode[0].point;
	scarfNode[0].tail += (startDirection - scarfNode[0].tail)*0.25;
	scarfNode[0].point = pos;

	/* draw */{
		clear();
		Vec2 pos = getParent()->getPosition() - getPosition() - getPosition().getNormalized()*20;
		for (int i = 0; i < Segments - 1; i++){
			drawSegment(
				scarfNode[i].point - pos, scarfNode[i + 1].point - pos, 5 + i / 10, Color4F(1.f, 0, 0, 1.f));
		}
	}
}

void Scarf::pushRotation(
	float _angle){

	angle = _angle;
}