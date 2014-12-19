#include "stdafx.h"
#include "Suction.h"

#include "Unit.h"
#include "Ally.h"
#include "Stage.h"

#include "common/resource.h"

#include "AttackData.h"

bool Suction::update(
	Unit *user,
	float remaining){

	auto ally = user->stage->ally[_OPPOSITE(user->ally)];

	AttackData attackData;
	attackData.user = user;
	attackData.object = user;
	attackData.damage = 0;
	attackData.position = user->position;
	attackData.radius = user->getAttribute(Attr::range).get();
	attackData.aggro = 1;

	ally->processAttack(attackData);
	return true;
}