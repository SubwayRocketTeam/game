#pragma once

#include "cocos2d.h"

#include "editor-support/cocostudio/CCSGUIReader.h"

class RoomScene : public cocos2d::Layer{
public:
	CREATE_FUNC(RoomScene);

	static cocos2d::Scene* scene();

protected:
	RoomScene();
	virtual ~RoomScene();

	virtual bool init();

	virtual void onInitGlobalObjects();
	virtual void onReleaseGlobalObjects();
};
