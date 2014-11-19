#include "pch.h"
#include "TrashPool.h"
#include "Trash.h"

#include "Stage.h"

#include <algorithm>

using namespace std;
using namespace cocos2d;

static TrashPool *instance = nullptr;

TrashPool::TrashPool(){
}
TrashPool::~TrashPool(){
}

TrashPool *TrashPool::create(){
	instance = new TrashPool();
	if(instance && instance->init())
		return instance;
	return nullptr;
}
TrashPool *TrashPool::getInstance(){
	return instance;
}
bool TrashPool::init(){
	if(!Node::init())
		return false;

	scheduleUpdate();

	return true;
}

void TrashPool::push(
	Trash *trash){

	trashes.pushBack(trash);
}
void TrashPool::remove(
	Trash *trash){

	trashes.eraseObject(trash);
}

void TrashPool::spawn(
	int count){

	auto stage = Stage::getInstance(0);
	for(int i=0;i<count;i++){
		auto trash = Trash::create();
		trash->setPosition(
			rand()%1600-800, rand()%1200-600);
		stage->addChild(trash);

		push(trash);
	}
}
Vector<Trash*> TrashPool::query(
	Rect rect){

	Vector<Trash*> objects;
	for(auto trash : trashes){
		auto trashPos = trash->getPosition();
		Rect trashRect =
			Rect(trashPos.x-25, trashPos.y-25, 50,50);

		if(trashRect.intersectsRect(rect))
			objects.pushBack(trash);
	}

	return objects;
}

void TrashPool::update(
	float dt){

	for(auto trash : trashes){

	}
}