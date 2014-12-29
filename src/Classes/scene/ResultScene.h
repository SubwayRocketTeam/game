#pragma once

#include "cocos2d.h"

#include "editor-support/cocostudio/CCSGUIReader.h"

class ResultScene : public cocos2d::Layer{
public:
	CREATE_FUNC(ResultScene);

	static cocos2d::Scene* scene();

protected:
	ResultScene();
	virtual ~ResultScene();

	virtual bool init();

	virtual void onInitGlobalObjects();
	virtual void onReleaseGlobalObjects();

	void onExitRoom(Ref *sender, ui::Widget::TouchEventType type);
};
