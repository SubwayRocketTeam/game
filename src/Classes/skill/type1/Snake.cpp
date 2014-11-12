#include "pch.h"
#include "Snake.h"

#include <queue>
#include <vector>

#include "objects/PartedBody.h"
#include "objects/Unit.h"
#include "objects/Ally.h"
#include "objects/Afterimage.h"
#include "common/resource.h"

#include "ui/StatusConsole.h"

using namespace std;
using namespace cocos2d;

static struct QueueItem{
	float distance;
	Unit *u;
};
static class Comp{
public:
	bool operator() (const QueueItem& lhs, const QueueItem&rhs) const{
		return lhs.distance > rhs.distance;
	}
};

void Snake::use(
	Unit *u,
	cocos2d::Vec2 pos){

	auto slash = Sprite::create(R::SkillSlash);
	auto ally = Ally::getInstance(
		_OPPOSITE(u->getAllyID()));

	priority_queue<QueueItem,vector<QueueItem>, Comp> q;

	for(auto enemy : *ally){
		QueueItem item;

		item.distance =
			u->getPosition().getDistance(enemy->getPosition());
		item.u = enemy;
		q.push(item);
	}

	Vector<FiniteTimeAction*> actions;
	Vec2 offset = u->getPosition();
	float moved = 0;
	while(!q.empty()){
		auto item = q.top(); q.pop();
		auto targetPos = item.u->getPosition();

		actions.pushBack(
			MoveTo::create(0.045, targetPos));

		moved += targetPos.getDistance(offset);
		offset = targetPos;

		if(moved >= 1000) break;
	}

	u->runAction(
		Sequence::create(actions));

	auto afterimage =  Afterimage::createWithPartedBody(
		u->getParent(),
		u->getBody(), duration);
	u->addChild(afterimage);
}