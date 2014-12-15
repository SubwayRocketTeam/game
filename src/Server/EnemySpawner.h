﻿#pragma once

#include "EnemyType.h"

class Enemy;
class Stage;

class EnemySpawner {
public:
	EnemySpawner(Stage* const stage);
	~EnemySpawner();

	void init();

	Enemy* spawn(EnemyType type);

public:
	Stage* const stage;
};
