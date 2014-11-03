#include "pch.h"

#include "BodyAnimation.h"

USING_NS_CC;

BodyAnimation::BodyAnimation()
{
	ZeroMemory(partAnimation, sizeof(partAnimation));
}

BodyAnimation* BodyAnimation::create(
	const std::string& filename, const std::vector<int>& partsId, const int frame)
{
	BodyAnimation* o = new BodyAnimation();
	if (o && o->init(filename, partsId, frame))
	{
		o->autorelease();
		return o;
	}
	CC_SAFE_DELETE(o);
	return nullptr;
}

bool BodyAnimation::init(
	const std::string& filename, const std::vector<int>& partsId, const int frame)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename + ".plist");

	for (int id : partsId)
	{
		Animation* anim = Animation::create();
		anim->setDelayPerUnit(AnimationDelay);
		for (int i = 1; i <= frame; ++i)
		{
			char buf[256];
			sprintf(buf, "%s_%d_%d.png", filename.c_str(), i, id);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);
			anim->addSpriteFrame(frame);
		}
		partAnimation[id - 1] = anim;
		anim->retain();
	}

	return true;
}

BodyAnimation::~BodyAnimation()
{
	for (auto anim : partAnimation)
	{
		CC_SAFE_RELEASE(anim);
	}
}


Animation* BodyAnimation::getPartAnimation(const int id)
{
	CCASSERT(id > 0 && id <= PartedBody::MaxParts, "BodyAnimation의 partAnimation id 범위를 초과함");
	return partAnimation[id - 1];
}
