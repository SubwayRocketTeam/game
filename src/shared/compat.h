#pragma once

#ifdef CC_TARGET_PLATFORM
	typedef cocos2d::Vec2 Vec2;
#else
	#include "Vec2.h"
#endif