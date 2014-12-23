#include "pch.h"
#include "AppDelegate.h"
#include "Compat.h"

#include "shared/JsonLoader.h"

#include "common/resource.h"
#include "common/PhysicsFactory.h"

#include "scene/GameScene.h"
#include "scene/LoginScene.h"
#include "scene/LobbyScene.h"

#include "skill/SkillPool.h"

#include "objects/Ally.h"
#include "objects/Stage.h"
#include "objects/EffectLayer.h"
#include "objects/EffectFactory.h"
#include "objects/TrashPool.h"
#include "objects/EnemyFactory.h"
#include "objects/GlobalResource.h"

#include "ui/Cursor.h"
#include "ui/StatusConsole.h"
#include "ui/Minimap.h"
#include "ui/SpawnIconPanel.h"
#include "ui/UpgradeBar.h"
#include "ui/TrashTank.h"

#include "network/Network.h"

using namespace cocos2d;
using namespace std;

AppDelegate::AppDelegate() {
}
AppDelegate::~AppDelegate() {
}

void AppDelegate::initGLContextAttrs(){
	GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Robotopia500");
        director->setOpenGLView(glview);
    }

	auto cache = SpriteFrameCache::getInstance();

	cache->addSpriteFramesWithFile(R::AfterimageGlowPlist);
	cache->addSpriteFramesWithFile(R::Hit1Plist);
	cache->addSpriteFramesWithFile(R::UnitsPlist);
	cache->addSpriteFramesWithFile(R::BulletsPlist);

	/* 전역적으로 계속 쓰이는 오브젝트 */
	Network::create();
	JsonLoader::create();

	auto network = Network::getInstance();
	network->open(Global::Host, 4321,
		[=](int result){
			if(result){
				
			}
	});

	glview->setDesignResolutionSize(
		1024,768, ResolutionPolicy::SHOW_ALL);
	glview->setFrameSize(
		1024,768);

	director->setOpenGLView(glview);
	director->setDisplayStats(true);
	director->setAnimationInterval(1.0 / Global::fps);
	
	auto scene = LoginScene::scene();
	director->runWithScene(scene);
	
	return true;
}

void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
}
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
}
