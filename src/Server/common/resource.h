#pragma once

#include <string>

#define _RESD(key, value) \
	const std::string key = value;
#define _RESL(key) \
	extern const std::string key;

namespace R{
	_RESL(SkillList);
}