#pragma once

#include "cocos2d.h"

#include "PartedBody.h"

class BodyAnimation : public cocos2d::Ref
{
public:
	static const float AnimationDelay;

public:
	static BodyAnimation* create(
		const std::string& filename, const std::vector<int>& partsId, const int frame);
	bool init(
		const std::string& filename, const std::vector<int>& partsId, const int frame);

	~BodyAnimation();

	cocos2d::Animation* getPartAnimation(const int id);

private:
	BodyAnimation();

private:
	cocos2d::Animation* partAnimation[PartedBody::MaxParts];
};