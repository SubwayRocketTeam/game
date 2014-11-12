#include "pch.h"
#include "Arrow.h"

#include "objects/PartedBody.h"
#include "objects/Unit.h"
#include "objects/Ally.h"
#include "common/resource.h"

#include "objects/Stage.h"

using namespace std;
using namespace cocos2d;

void rayCast(){
	auto enemies = Ally::getInstance(Ally::Type::allyEnemy);


}

void Arrow::use(
	Unit *u,
	cocos2d::Vec2 pos){

	auto ally = Ally::getInstance(
		_OPPOSITE(u->getAllyID()));
	auto world =
		Director::getInstance()->getRunningScene()
		->getPhysicsWorld();

	auto body = u->getPhysicsBody();
	auto end =
		(pos - u->getPosition()).getNormalized() * 1000;
	Unit *target = nullptr;

	world->rayCast(
		[&](PhysicsWorld &world, const PhysicsRayCastInfo &info, void *data){
		printf("contact %s \n", typeid(*info.shape->getBody()->getNode()).name());
			if(info.shape == u->getPhysicsBody()->getShape(0))
				return true;

			target = (Unit*)info.shape->getBody()->getNode();
			return false;
	}, u->getPosition(), end, nullptr);

	AttackData ad;
	ad.type = AttackType::Target;
	ad.target = target;
		
	
	printf("%f %f / %f %f\n", 
		u->getPhysicsBody()->getPosition().x, u->getPhysicsBody()->getPosition().y,
		end.x, end.y);
	printf("%x\n", target);

	//ally->processAttack(u, ad);
}