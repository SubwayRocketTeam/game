#pragma once

class Unit;

class CollisionDetector {
public:
	void init();

	void update(float dt);

	void addUnit(Unit* unit);		// Stage에서만 불러야 한다.
	void removeUnit(Unit* unit);	// Stage에서만 불러야 한다.

protected:
	std::vector<Unit*> unitVector;
};