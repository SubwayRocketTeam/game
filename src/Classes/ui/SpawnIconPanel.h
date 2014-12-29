#pragma once

#include "cocos2d.h"
#include "common/max.h"

#include "objects/KeyboardEventListener.h"

#include <map>

class SpawnIcon;

class SpawnIconPanel : public cocos2d::Node,
	public KeyboardEventListener{
public:
	static SpawnIconPanel *create();
	static SpawnIconPanel *getInstance();

	void setIconList(
		int id[Max::Enemies]);

	void use(
		int id);

protected:
	virtual bool init();

	void processSpawn(
		cocos2d::EventKeyboard::KeyCode code);
	virtual void onKeyboardDown(
		cocos2d::EventKeyboard::KeyCode code);

	void updateCooltime(
		float dt);

	virtual void onExit();

private:
	std::map<int, SpawnIcon *> icons;
	std::map<int, float> cooltimes;
};