#if defined(_CLIENT)
	#include "cocos2d.h"
	#define Vec2 cocos2d::Vec2
#elif defined(_SERVER)
	#include "Vec2.h"
#endif