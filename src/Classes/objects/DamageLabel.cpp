﻿#include "pch.h"
#include "DamageLabel.h"

#include "tags.h"

using namespace cocos2d;

DamageLabel::DamageLabel() :
	counter(1){
}
DamageLabel::~DamageLabel(){
}

DamageLabel *DamageLabel::create(){
	DamageLabel *e = new DamageLabel();

	if(e && e->init()){
		e->autorelease();
		return e;
	}
	CC_SAFE_DELETE(e);
	return nullptr;
}
bool DamageLabel::init(){
	if(!LabelTTF::initWithString("","arial", FontSize))
		return false;

	setColor(Color3B::RED);

	return true;
}

void DamageLabel::active(){
	char dmg[32];
	sprintf(dmg, "-%d", counter++);

	stopActionByTag(ActionType::Fade);
	setString(dmg);
	setOpacity(255);

	unschedule(SEL_SCHEDULE(&DamageLabel::fadeOut));
	schedule(SEL_SCHEDULE(&DamageLabel::fadeOut), 1);
}
void DamageLabel::fadeOut(
	float dt){

	counter = 1;
	runAction(
		Spawn::create(
			FadeOut::create(0.1),
			nullptr
		))
		->setTag(ActionType::Fade);
}