#pragma once

#include "shared/compat.h"

#include "Skill.h"

class Unit;

class ActiveSkill : public Skill{
public:
	float cooltime;
	float cost;

public:
	virtual void use(
		Unit *u,
		Vec2 pos);
	virtual void update(
		Unit *u,
		float dt);

protected:
	virtual bool initExternalData(
		const std::string &dataPath);
};

#include "shared/end_compat.h"