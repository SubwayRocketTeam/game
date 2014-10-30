#pragma once

#include "cocos2d.h"
#include "Unit.h"

class Enemy;

class EnemySpawner : public Unit{
public:
	static EnemySpawner *create();

    virtual bool init();

	/* ���� ��ġ�� �� ���� (�׽�Ʈ��) */
	void spawn();

protected:
	EnemySpawner();
	virtual ~EnemySpawner();
};
