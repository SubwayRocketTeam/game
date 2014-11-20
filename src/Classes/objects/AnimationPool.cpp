#include "pch.h"

#include "AnimationPool.h"

USING_NS_CC;

static AnimationPool* instance = nullptr;

AnimationPool* AnimationPool::create()
{
	AnimationPool* o = new AnimationPool();
	if (o && o->init())
	{
		o->autorelease();

		CC_SAFE_RELEASE(instance);
		CC_SAFE_DELETE(instance);
		instance = o;
		
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

void AnimationPool::add(Animation* const animation, const std::string& name)
{
	if (pool.find(name) != pool.end())
		pool[name]->release();
	pool[name] = animation;
	animation->retain();
}


Animation* AnimationPool::getAnimation(const std::string& name)
{
	if (pool.find(name) != pool.end())
		return pool[name];
	else
		return nullptr;
}
