#pragma once

#include "Vec2.h"

class Unit;

class TrashPool {
public:
	TrashPool(Stage* const stage);
	~TrashPool();

	void init();

	void update(float dt);

	void spawn(int count = 0);
	void spawn(const Vec2 &pos,	int count = 0);

	void push(Unit *trash);		// Stage������ �ҷ��� �Ѵ�.
	void remove(Unit *trash);	// Stage������ �ҷ��� �Ѵ�.

public:
	Stage* const stage;

private:
	std::vector<Unit*> trashes;
};
