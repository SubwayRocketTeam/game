#pragma once

/* deprecated */
#pragma warning (disable : 4996)
/* code-page */
#pragma warning (disable : 4819)

#define __CLASS__ \
	typeid(*this).name()

#include "cocos2d.h"

#include "common/global.h"
#include "common/max.h"
#include "common/zorder.h"
#include "common/makepath.h"

extern float ping;