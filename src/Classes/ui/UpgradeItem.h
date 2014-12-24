#pragma once

#include "cocos2d.h"

class UpgradeItem : public cocos2d::Sprite{
public:
	static UpgradeItem *create(
		int id);

	void upgrade();

protected:
	UpgradeItem();
	virtual bool init(
		int id);

private:
	cocos2d::ProgressTimer *progress;
	int level;

};