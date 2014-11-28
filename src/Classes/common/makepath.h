#pragma once

#define _MAX_RESULT 256
#define _MAKE_PATH(fmt, ...) \
	[&](){ \
		char tmp[_MAX_RESULT]; \
		sprintf(tmp, fmt, __VA_ARGS__); \
		return std::string(tmp); \
	}()

/* Usage
 *
 *   Sprite::initWithFile(_MAKE_PATH("%d.png", path))
 */