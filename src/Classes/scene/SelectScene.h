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


	virtual void onInitGlobalObjects();
	virtual void onReleaseGlobalObjects();

	void onSelectRobot(
		Ref *sender, ui::Widget::TouchEventType type, int robot);
	void onSelectTeam(
		Ref *sender, ui::Widget::TouchEventType type, int team);
	void onReady(
		Ref *sender, ui::Widget::TouchEventType type);
	void onExitRoom(
		Ref *sender, ui::Widget::TouchEventType type);

protected:
	int selectedRobot;
};
