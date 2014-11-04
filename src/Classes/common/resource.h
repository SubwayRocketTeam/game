#pragma once

#include <string>

#define _RESD(key, value) \
	const std::string key = value;
#define _RESL(key) \
	extern const std::string key;

namespace R{
	_RESL(Minimap);

	_RESL(PlayerBody);
	_RESL(EnemyBody);

	_RESL(StageFloor);
	_RESL(StageJson);

	_RESL(EnemySpawner);

	_RESL(SkillList);

	_RESL(SkillSlash);

	_RESL(Cursor);

	_RESL(Run);
};