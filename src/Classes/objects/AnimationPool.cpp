#include "pch.h"

#include "AnimationPool.h"
#include "BodyAnimation.h"

USING_NS_CC;

static AnimationPool* instance = nullptr;

AnimationPool* AnimationPool::create()
{
	AnimationPool* o = new AnimationPool();
	if (o && o->init())
	{
		o->autorelease();
		return o;
	}

	CC_SAFE_DELETE(o);
	return nullptr;
}

AnimationPool* AnimationPool::getInstance()
{
	return instance;
}

bool AnimationPool::init()
{
	return true;
}

bool AnimationPool::loadFromFile(const std::string& filename)
{
	// TODO: JSON을 읽어서 애니메이션 파일을 로드
	return true;
}

void AnimationPool::add(BodyAnimation* const animation, const std::string& name)
{
	if (pool.find(name) != pool.end())
		pool[name]->release();
	pool[name] = animation;
	animation->retain();
}


BodyAnimation* AnimationPool::getBodyAnimation(const std::string& name)
{
	if (pool.find(name) != pool.end())
		return pool[name];
	else
		return nullptr;
}
