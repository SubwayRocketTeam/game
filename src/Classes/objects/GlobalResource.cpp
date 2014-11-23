#include "pch.h"
#include "GlobalResource.h"

static GlobalResource *instance = nullptr;

GlobalResource::GlobalResource() :
	gold(0), trash(0){
}
GlobalResource::~GlobalResource(){
}

GlobalResource *GlobalResource::create(){
	instance = new GlobalResource();

	if(instance)
		return instance;
	
	CC_SAFE_DELETE(instance);
	return nullptr;
}
GlobalResource *GlobalResource::getInstance(){
	return instance;
}