#pragma once

class Unit;

class CollisionDetector {
public:
	void init();

	void update(float dt);

	void addUnit(Unit* unit);		// Stage������ �ҷ��� �Ѵ�.
	void removeUnit(Unit* unit);	// Stage������ �ҷ��� �Ѵ�.

protected:
	std::vector<Unit*> unitVector;
};