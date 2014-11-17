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
#include "objects/TrashPool.h"

#include "ui/Cursor.h"
#include "ui/StatusConsole.h"
#include "ui/Minimap.h"
#include "ui/UserResources.h"
#include "ui/SkillIconPanel.h"

#include "common/resource.h"

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
		glview = GLViewImpl::createWithFullScreen("Robotopia");
        director->setOpenGLView(glview);
    }

	auto cache = SpriteFrameCache::getInstance();

	cache->addSpriteFramesWithFile(R::AfterimageGlowPlist);
	cache->addSpriteFramesWithFile(R::Hit1Plist);

	TrashPool::create();
	Network::create();
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
	SkillIconPanel::create();

	auto network = Network::getInstance();
	network->open("localhost", 9916,
		[=](int result){
			if(result){
				network->sendLoginRequest(
					"pjc0247", "asdf1234");
			}
	});

	network->route<login_response>(id_login_response,
		[](login_response *pkt){
			printf("%d\n", pkt->result);
	});

	glview->setDesignResolutionSize(
		1024,768, ResolutionPolicy::SHOW_ALL);
	glview->setFrameSize(
		1024,768);

	director->setOpenGLView(glview);
	director->setDisplayStats(false);
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
