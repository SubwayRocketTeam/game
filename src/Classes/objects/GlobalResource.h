#pragma once

#include "cocos2d.h"

class GlobalResource : public cocos2d::Ref{
public:
	static GlobalResource *create();
	static GlobalResource *getInstance();

protected:
	GlobalResource();
	virtual ~GlobalResource();

public:
	int gold;
	int trash;
};