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

	void onLogin(
		cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onDescription(
		cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onValley(
		cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
};
