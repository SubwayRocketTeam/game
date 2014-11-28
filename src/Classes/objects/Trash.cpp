﻿#include "pch.h"
#include "Trash.h"
#include "TrashPool.h"

using namespace cocos2d;

Trash::Trash(){
}
Trash::~Trash(){
}

Trash *Trash::create(){
	Trash *t = new Trash();

	if(t && t->init()){
		t->autorelease();
		return t;
	}
	CC_SAFE_DELETE(t);
	return nullptr;
}
bool Trash::init(){
	int type = rand() % 6+1;
	char path[128];
	sprintf(path, "trashs%d", type);

	if(!Unit::init(path))
		return false;

	setRotation(rand() % 360);
	
	return true;
}

void Trash::sweep(){
	auto trashPool = TrashPool::getInstance();
	trashPool->remove(this);

	runAction(
		Sequence::create(
			Spawn::create(
				FadeOut::create(0.3),
				ScaleTo::create(0.3, 2.5),
				nullptr),
			RemoveSelf::create(),
			nullptr
		));
}