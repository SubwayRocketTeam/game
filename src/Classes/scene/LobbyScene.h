#pragma once

#include "cocos2d.h"

#include "editor-support/cocostudio/CCSGUIReader.h"

class LobbyScene : public cocos2d::Layer{
public:
	CREATE_FUNC(LobbyScene);

    static cocos2d::Scene* scene();

protected:
	LobbyScene();
	virtual ~LobbyScene();

	virtual bool init();
};
