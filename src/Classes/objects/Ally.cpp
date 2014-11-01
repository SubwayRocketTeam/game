#include "pch.h"
#include "Ally.h"

#include "Unit.h"

Ally *Ally::create(){
	Ally *a = new Ally();

	if(a && a->init()){
		a->autorelease();
		return a;
	}
	CC_SAFE_DELETE(a);
	return nullptr;
}

bool Ally::init(){
	
	return true;
}

void Ally::push(
	Unit *u){

	members.pushBack(u);
}
void Ally::remove(
	Unit *u){

	members.eraseObject(u);
}