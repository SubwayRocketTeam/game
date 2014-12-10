#pragma once

#include "EnemyType.h"

class Enemy;

class EnemySpawner {
public:
	EnemySpawner();
	~EnemySpawner();

	bool init();

	void spawn(EnemyType type);
};
