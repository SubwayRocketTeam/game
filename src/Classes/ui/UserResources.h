#pragma once

#include "cocos2d.h"

class UserResources : public cocos2d::Node  {
public:
	static UserResources* create();
	static UserResources* getInstance();

	void setLevel(int _level);
	void setExpAndMaxExp(int _exp, int _maxExp);
	void setGold(int _gold);

	virtual bool init() override;
private:
	UserResources();
	virtual ~UserResources();

	cocos2d::LabelTTF* levelLabel;
	cocos2d::LabelTTF* expLabel;
	cocos2d::LabelTTF* goldLabel;
};