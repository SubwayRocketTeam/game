#pragma once

#include "cocos2d.h"

#include <string>

class PartedBody : public cocos2d::Sprite{
public:
	static const int Parts = 6;

public:
	static PartedBody *create(
		const std::string &prefix);
	virtual bool init(
		const std::string &prefix);

	virtual float getRotation() const;
	virtual void setRotation(
		float angle);

protected:
	PartedBody();
	virtual ~PartedBody();

	void updateCharacter(float dt);

protected:
	cocos2d::Sprite *body[Parts];
};
