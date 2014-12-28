#pragma once

#include "cocos2d.h"

#include "editor-support/cocostudio/CCSGUIReader.h"

class WaitingScene : public cocos2d::Layer{
public:
	CREATE_FUNC(WaitingScene);

	static cocos2d::Scene* scene();

protected:
	WaitingScene();
	virtual ~WaitingScene();

	virtual bool init();

	virtual void onInitGlobalObjects();
	virtual void onReleaseGlobalObjects();
};
