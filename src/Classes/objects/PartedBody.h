#pragma once

#include "cocos2d.h"

#include <vector>

class BodyAnimation;

class PartedBody : public cocos2d::Sprite{
public:
	static const int MaxParts = 6;

public:
	static PartedBody *create(
		const std::string &imageName, const int part);

	virtual bool init(
		const std::string &imageName, const int part);

	virtual float getRotation() const override;
	virtual void setRotation(float angle) override;

	void runAnimation(BodyAnimation* const animation, bool repeatForever = false);
	void stopAnimation(const int id);
	void stopAllAnimation();

	cocos2d::Vec2 getHeadPosition();

	std::vector<cocos2d::Sprite*>::iterator begin();
	std::vector<cocos2d::Sprite*>::iterator end();

	float getOriginY();
	float getBodyHeight();
	float getBodyWidth();

protected:
	PartedBody();
	virtual ~PartedBody();

	void updateCharacter(float dt);
	bool makeBodyPart(const std::string partName, const int partId);

protected:
	int partNum;

	std::vector<cocos2d::Sprite*> body;
	std::vector<cocos2d::SpriteFrame*> bodyOriginal;
	std::vector<cocos2d::Animation*> runningAnimation;
};
