#include "AppDelegate.h"

#include <vector>
#include <string>

#include "AppMacros.h"

#include "scene/GameScene.h"
#include "common/PhysicsFactory.h"

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
        glview = GLView::create("Cpp Empty Test");
        director->setOpenGLView(glview);
    }

	PhysicsFactory::create();

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
