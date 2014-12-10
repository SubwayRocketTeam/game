#pragma once

class Unit;

class CollisionDetector {
public:
	void init();

	void update(float dt);

	void addUnit(Unit* unit);
	void removeUnit(Unit* unit);

protected:
	std::vector<Unit*> unitVector;
};