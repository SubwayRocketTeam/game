#include "pch.h"
#include "AppDelegate.h"
#include "Compat.h"

#include "scene/GameScene.h"
#include "common/PhysicsFactory.h"
#include "common/EffectFactory.h"

#include "skill/SkillPool.h"

#include "objects/Ally.h"
#include "objects/Stage.h"
#include "objects/EffectLayer.h"

#include "ui/Cursor.h"
#include "ui/StatusConsole.h"
#include "ui/Minimap.h"
#include "ui/UserResources.h"

#include "common/resource.h"

using namespace cocos2d;
using namespace std;

AppDelegate::AppDelegate() {
}
AppDelegate::~AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Cpp Empty Test");
        director->setOpenGLView(glview);
    }

	auto cache = SpriteFrameCache::getInstance();

	cache->addSpriteFramesWithFile(R::AfterimageGlowPlist);
	cache->addSpriteFramesWithFile(R::Hit1Plist);
	cache->addSpriteFramesWithFile(R::DashPlist);

	EffectLayer::create();
	EffectFactory::create();
	Minimap::create();
	Stage::create();
	Ally::create();
	StatusConsole::create();
	SkillPool::create();
	PhysicsFactory::create();
	Cursor::create();
	UserResources::create();

	glview->setDesignResolutionSize(
		800,600, ResolutionPolicy::SHOW_ALL);
	glview->setFrameSize(
		800,600);

	director->setOpenGLView(glview);
	director->setDisplayStats(true);
	director->setAnimationInterval(1.0 / Global::fps);
	
	auto scene = GameScene::scene();
	director->runWithScene(scene);
	
	return true;
}

void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
}
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
}
