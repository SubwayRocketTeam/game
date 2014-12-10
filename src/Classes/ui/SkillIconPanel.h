#pragma once

#include "cocos2d.h"
#include "common/max.h"

#include "objects/KeyboardEventListener.h"

#include <map>

class SkillIcon;

class SkillIconPanel : public cocos2d::Sprite,
	public KeyboardEventListener{
public:
	static SkillIconPanel *create();
	static SkillIconPanel *getInstance();

	void setSkillList(
		int id[Max::Skills]);

	void use(
		int id);

protected:
	virtual bool init();

	void processSpawn(
		cocos2d::EventKeyboard::KeyCode code);
	virtual void onKeyboardDown(
		cocos2d::EventKeyboard::KeyCode code);

private:
	std::map<int, SkillIcon *> icons;
};