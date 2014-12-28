#pragma once

#include "cocos2d.h"

#include "editor-support/cocostudio/CCSGUIReader.h"

class LoginScene : public cocos2d::Layer{
public:
	CREATE_FUNC(LoginScene);

	static cocos2d::Scene* scene();


protected:
	LoginScene();
	virtual ~LoginScene();

	virtual bool init();

	virtual void onEnter();

	void onLogin(
		cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
};
