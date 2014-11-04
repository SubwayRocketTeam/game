#include "pch.h"
#include "AppDelegate.h"
#include "Compat.h"

#include "scene/GameScene.h"
#include "common/PhysicsFactory.h"

#include "skill/SkillPool.h"

#include "objects/Ally.h"

#include "ui/Cursor.h"
#include "ui/StatusConsole.h"

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

	ShowCursor(false);

	Ally::create();
	StatusConsole::create();
	SkillPool::create();
	PhysicsFactory::create();
	Cursor::create();

	glview->setDesignResolutionSize(
		800,600, ResolutionPolicy::SHOW_ALL);
	glview->setFrameSize(
		800,600);

	director->setOpenGLView(glview);
	director->setDisplayStats(true);
	director->setAnimationInterval(1.0 / 60);
	
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
