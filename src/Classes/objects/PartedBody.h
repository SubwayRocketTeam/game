#pragma once

#include "cocos2d.h"

class BodyAnimation;

class PartedBody : public cocos2d::Sprite{
public:
	static const int MaxParts = 6;

public:
	static PartedBody *create(
		const std::string &filename);
	static PartedBody *create(
		const std::string &prefix, const int part);

	virtual bool init(
		const std::string &filename);
	virtual bool init(
		const std::string &prefix, const int part);

	virtual float getRotation() const override;
	virtual void setRotation(float angle) override;

	void runAnimation(BodyAnimation* const animation);
	void stopAnimation(const int id);
	void stopAllAnimation();

	cocos2d::Vec2 getHeadPosition();

protected:
	PartedBody();
	virtual ~PartedBody();

	void updateCharacter(float dt);

protected:
	int partNum;

	cocos2d::Sprite* body[MaxParts];
	cocos2d::Texture2D* bodyTexture[MaxParts];
	cocos2d::Animation* runningAnimation[MaxParts];
};
