#pragma once

#include "Vec2.h"

class Trash;

class TrashPool {
public:
	TrashPool();
	~TrashPool();

	bool init();

	void update(float dt);

	void spawn(int count = 0);
	void spawn(const Vec2 &pos,	int count = 0);

	void push(Trash *trash);
	void remove(Trash *trash);

private:
	std::vector<Trash*> trashes;
};
