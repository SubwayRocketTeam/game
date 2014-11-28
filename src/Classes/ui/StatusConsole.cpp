#include "pch.h"
#include "StatusConsole.h"

using namespace std;
using namespace cocos2d;

static StatusConsole *instance = nullptr;

StatusConsole::StatusConsole(){
}
StatusConsole::~StatusConsole(){
}

StatusConsole* StatusConsole::create(){
	instance = new StatusConsole();

	if (instance && instance->init()) {
		instance->autorelease();
		return instance;
	}
	CC_SAFE_DELETE(instance);
	return nullptr;
}
bool StatusConsole::init(){
	if(!Sprite::init())
		return false;

	return true;
}
StatusConsole* StatusConsole::getInstance(){
	return instance;
}

void StatusConsole::output(
	const string &msg){

	shift();
	addLine(msg);
}

void StatusConsole::shift(){
	for(auto line : lines){
		line->runAction(
			MoveBy::create(0.0, Vec2(0,LineSize)));
	}
	if(lines.size() >= MaxLines){
		lines.front()->runAction(
			Sequence::create(
				FadeOut::create(0.5),
				RemoveSelf::create(),
				nullptr
			));
		lines.pop_front();
	}
}
void StatusConsole::addLine(
	const std::string &msg){

	auto label = LabelTTF::create(
		msg, "arial", LineSize);
	label->setColor(Color3B::RED);
	label->setOpacity(0);
	label->setAnchorPoint(Vec2(0,0));
	label->setPosition(
		Vec2(0, MaxLines*5));
	label->runAction(
		Spawn::create(
			MoveBy::create(0.0, Vec2(0,LineSize)),
			FadeIn::create(0.0),
			nullptr
		));

	addChild(label);
	lines.push_back(label);
}