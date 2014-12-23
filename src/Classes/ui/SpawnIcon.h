#pragma once

#include "cocos2d.h"

class SpawnIcon : public cocos2d::Sprite{
public:
	static SpawnIcon *create(
		int id);

	void use();

	int getCost();
	float getCooltime();

protected:
	SpawnIcon();
	virtual bool init(
		int id);

private:
	int id;
	cocos2d::ProgressTimer *icon;

	int cost;
	float cooltime;
};