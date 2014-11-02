#pragma once

#include "cocos2d.h"

#include "PartedBody.h"

class BodyAnimation : public cocos2d::Ref
{
public:
	static const int AnimationDelay = 1.f;

public:
	static BodyAnimation* create(
		const std::string& filename, const std::vector<int>& partsId, const int frame);
	bool init(
		const std::string& filename, const std::vector<int>& partsId, const int frame);

	cocos2d::Animation* getPartAnimation(const int id);

private:
	BodyAnimation();

private:
	cocos2d::Animation* partAnimation[PartedBody::MaxParts];
};