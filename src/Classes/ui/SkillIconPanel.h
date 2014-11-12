#pragma once

#include "cocos2d.h"
#include "common/max.h"

#include <map>

class SkillIcon;

class SkillIconPanel : public cocos2d::Sprite{
public:
	static SkillIconPanel *create();
	static SkillIconPanel *getInstance();

	void setSkillList(
		int id[Max::Skills]);

	void use(
		int id);

protected:
	virtual bool init();

private:
	std::map<int, SkillIcon *> icons;
};