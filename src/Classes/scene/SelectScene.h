#pragma once

#include "cocos2d.h"

#include "editor-support/cocostudio/CCSGUIReader.h"

class SelectScene : public cocos2d::Layer{
public:
	CREATE_FUNC(SelectScene);

	static cocos2d::Scene* scene();

	void refreshRoom();

protected:
	SelectScene();
	virtual ~SelectScene();

	virtual bool init();

	void selectRobot(int robot);

	virtual void onInitGlobalObjects();
	virtual void onReleaseGlobalObjects();

	virtual void onEnter();

	void onSelectRobot(
		Ref *sender, cocos2d::ui::Widget::TouchEventType type, int robot);
	void onSelectTeam(
		Ref *sender, cocos2d::ui::Widget::TouchEventType type, int team);
	void onReady(
		Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onExitRoom(
		Ref *sender, cocos2d::ui::Widget::TouchEventType type);

protected:
	int selectedRobot;
};
