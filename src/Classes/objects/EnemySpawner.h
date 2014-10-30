#pragma once

#include "cocos2d.h"
#include "Unit.h"

class Enemy;

class EnemySpawner : public Unit{
public:
	static EnemySpawner *create();

    virtual bool init();

	/* 랜덤 위치에 적 스폰 (테스트용) */
	void spawn();

protected:
	EnemySpawner();
	virtual ~EnemySpawner();
};
