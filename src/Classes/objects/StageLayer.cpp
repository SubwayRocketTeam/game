#include "pch.h"
#include "StageLayer.h"

#include "Stage.h"
#include "ControlablePlayer.h"

using namespace cocos2d;

static const int actionSwitchStage = 1;

StageLayer::StageLayer() :
	activeStageID(0){
}
StageLayer::~StageLayer(){
}

StageLayer *StageLayer::create(){
	StageLayer *s = new StageLayer();

	if(s && s->init()){
		s->autorelease();
		return s;
	}
	CC_SAFE_DELETE(s);
	return nullptr;
}
bool StageLayer::init(){
	if(!Layer::init())
		return false;

	auto director = Director::getInstance();
	auto visibleSize = director->getVisibleSize();
	auto origin = director->getVisibleOrigin();

	for(int i=0;i<Max::Teams;i++){
		auto stage = Stage::getInstance(i);
		stage->setPosition(origin + visibleSize / 2);
		stage->setCascadeOpacityEnabled(true);
		addChild(stage);

		if(i != activeStageID){
			stage->setVisible(false);
			stage->setOpacity(0);
		}
	}

	enableKeyboardInput(this);

	return true;
}

void StageLayer::switchStage(){
	auto size =
		Director::getInstance()->getWinSize();
	auto player = ControlablePlayer::getInstance();
	Stage *stage;

	/* 이전 스테이지 FadeOut */
	stage = Stage::getInstance(activeStageID);
	stage->stopAllActionsByTag(
		actionSwitchStage);
	stage->runAction(
		Sequence::create(
			Spawn::create(
				FadeTo::create(0.2, 0),
				ScaleTo::create(0.2, 1,1),
				nullptr),
			Hide::create(),
			nullptr
		))
		->setTag(actionSwitchStage);

	/* 기본적으로 2팀임을 가정 */
	activeStageID ^= 1;

	auto stageSize = stage->getContentSize();
	Size ratio; 
	
	if(player->getStageID() == activeStageID)
		ratio.setSize(1,1);
	else{
		ratio.setSize(
			size.width / stageSize.width,
			size.height / stageSize.height);
	}

	/* 새 스테이지 FadeIn */
	stage = Stage::getInstance(activeStageID);
	stage->stopAllActionsByTag(
		actionSwitchStage);
	stage->runAction(
		Sequence::create(
			Show::create(),
			Spawn::create(
				FadeTo::create(0.1, 255),
				ScaleTo::create(0.1, ratio.width,ratio.height),
				nullptr),
			nullptr
		))
		->setTag(actionSwitchStage);
}

void StageLayer::onKeyboardDown(
	cocos2d::EventKeyboard::KeyCode keycode){

	/* 보이는 스테이지 전환 */
	if(keycode == EventKeyboard::KeyCode::KEY_TAB){
		switchStage();
	}
}
void StageLayer::onKeyboardUp(
	cocos2d::EventKeyboard::KeyCode keycode){

	if(keycode == EventKeyboard::KeyCode::KEY_TAB){
		switchStage();
	}
}