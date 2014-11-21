#include "pch.h"
#include "EnemyFactory.h"

#include "Enemy.h"

#include "skill/SkillPool.h"
#include "skill/id.h"

USING_NS_CC;

Enemy* EnemyFactory::createEnemy(EnemyType type)
{
	Enemy* enemy = Enemy::create();

	switch (type)
	{
	case enemyBasic:
		break;
	case enemyShooting:
		enemy->setSkill((ActiveSkill*)SkillPool::getInstance()->get(skillSlash));
		break;
	default:
		break;
	}

	return enemy;
}
