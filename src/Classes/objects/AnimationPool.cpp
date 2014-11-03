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
	// TODO: JSON�� �о �ִϸ��̼� ������ �ε�
	return true;
}

void AnimationPool::add(BodyAnimation* const animation, const std::string& name)
{
	pool[name] = animation;
}


BodyAnimation* AnimationPool::getBodyAnimation(const std::string& name)
{
	if (pool.find(name) != pool.end())
		return pool[name];
	else
		return nullptr;
}
