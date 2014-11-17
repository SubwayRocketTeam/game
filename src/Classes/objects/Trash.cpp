#include "pch.h"
#include "Trash.h"

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
	
	return true;
}