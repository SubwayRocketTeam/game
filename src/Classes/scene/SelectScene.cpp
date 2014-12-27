#include "pch.h"
#include "SelectScene.h"
#include "GameScene.h"

#include "ext/uiProgressTo.h"

#include "ui/UILoadingBar.h"

using namespace std;
using namespace cocos2d;
using namespace cocostudio;

SelectScene::SelectScene(){
}
SelectScene::~SelectScene(){
}

Scene* SelectScene::scene(){
	auto scene = Scene::create();
	SelectScene *layer = SelectScene::create();
	scene->addChild(layer);
	return scene;
}

bool SelectScene::init(){
	if(!Layer::init())
		return false;
	
	auto reader = GUIReader::getInstance();
	auto layout = reader->widgetFromJsonFile("select_scene.json");

	addChild(layout);

	((ui::Widget*)layout->getChildByName("btn_start"))
		->addClickEventListener(CC_CALLBACK_1(SelectScene::onStart, this));

	auto infos = layout->getChildByName("pn_info");
	auto pbAttack = (ui::LoadingBar*)infos->getChildByName("pb_attack");
	auto pbSpeed = (ui::LoadingBar*)infos->getChildByName("pb_speed");
	auto pbRange = (ui::LoadingBar*)infos->getChildByName("pb_range");

	auto robots = layout->getChildByName("pn_robot");

	/* TODO : 개판 수정 */
	for(auto robot : robots->getChildren()){
		int attack = rand()%60 + 40;
		int speed = rand()%60 + 40;
		int range = rand()%60 + 40;

		((ui::Widget*)robot)
			->addClickEventListener(
				[=](Ref *sender){
					robot->runAction(
						Sequence::create(
							ScaleTo::create(0.23/2, 1.1, 0.95),
							ScaleTo::create(0.17/2, 0.9 ,1.1),
							ScaleTo::create(0.15/2, 1.05, 0.95),
							ScaleTo::create(0.08/2, 1,1),
							nullptr
						));
					pbAttack->runAction( EaseElasticOut::create(UiProgressTo::create(0.6, attack)) );
					pbSpeed->runAction( EaseElasticOut::create(UiProgressTo::create(0.6, speed)) );
					pbRange->runAction( EaseElasticOut::create(UiProgressTo::create(0.6, range)) );
			});
	}


	return true;
}

void SelectScene::onStart(
	Ref *sender){

	auto scene = GameScene::scene();
	Director::getInstance()
		->replaceScene(scene);
}
void SelectScene::onSelectRobot(
	Ref *sender){


}

void SelectScene::onInitGlobalObjects(){
}
void SelectScene::onReleaseGlobalObjects(){
}