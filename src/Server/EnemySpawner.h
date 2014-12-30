#pragma once

#include "EnemyType.h"
#include "Vec2.h"

class Enemy;
class Stage;

class EnemySpawner {
public:
	EnemySpawner(Stage* const stage);
	~EnemySpawner();

	void init();

	Enemy* spawn(EnemyType type);
	Enemy* spawn(EnemyType type, const Vec2& position);

public:
	Stage* const stage;
};
