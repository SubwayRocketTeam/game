#pragma once

#include "cocos2d.h"

#include "editor-support/cocostudio/CCSGUIReader.h"

class SelectScene : public cocos2d::Layer{
public:
	CREATE_FUNC(SelectScene);

    static cocos2d::Scene* scene();

protected:
	SelectScene();
	virtual ~SelectScene();

	virtual bool init();

	void onStart(
		cocos2d::Ref *sender);
	void onSelectRobot(
		cocos2d::Ref *sender);

	virtual void onInitGlobalObjects();
	virtual void onReleaseGlobalObjects();
};
