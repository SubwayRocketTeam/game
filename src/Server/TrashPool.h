#pragma once

#include "Vec2.h"

class Trash;
class Stage;

class TrashPool {
public:
	TrashPool(Stage* const stage);
	~TrashPool();

	void init();

	void update(float dt);

	void spawn(int count = 0);
	void spawn(const Vec2 &pos,	int count = 0);

	std::vector<Trash*> query(float x, float y, float w, float h);

	void push(Trash *trash);	// Stage������ �ҷ��� �Ѵ�.
	void remove(Trash *trash);	// Stage������ �ҷ��� �Ѵ�.

public:
	Stage* const stage;

private:
	std::vector<Trash*> trashes;
};
