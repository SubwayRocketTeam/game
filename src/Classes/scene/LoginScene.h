#pragma once

#include "cocos2d.h"

class LoginScene : public cocos2d::Layer{
public:
	CREATE_FUNC(LoginScene);

    static cocos2d::Scene* scene();

protected:
	LoginScene();
	virtual ~LoginScene();

	virtual bool init();
};
