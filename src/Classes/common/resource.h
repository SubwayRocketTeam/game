#pragma once

#include <string>

#define _RESD(key, value) \
	const std::string key = value;
#define _RESL(key) \
	extern const std::string key;

namespace R{
	_RESL(AfterimageGlowPlist);
	_RESL(Hit1Plist);

	_RESL(SkillPanel);
	_RESL(SkillIconOverlay);

	_RESL(Bullet);

	_RESL(Hit1);

	_RESL(Minimap);

	_RESL(UpgradeBar);

	_RESL(PlayerBody);
	_RESL(EnemyBody);

	_RESL(StageFloor);
	_RESL(StageJson);
	_RESL(RepairArea);

	_RESL(EnemySpawner);

	_RESL(SkillList);

	_RESL(SkillSlash);

	_RESL(Cursor);

	_RESL(Run);

	_RESL(HPGauge);
	_RESL(MPGauge);

	_RESL(BGM);
	_RESL(Fire);
};