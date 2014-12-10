#pragma once

#define _OPPOSITE(id) \
	((Ally::Type) (((int)id) ^ 1))

class Unit;
struct AttackData;

class Ally {
public:
	enum Type{
		allyPlayer = 0,
		allyEnemy
	};

public:
	void init();

	void push(Unit *u);		// Stage������ �ҷ��� �Ѵ�.
	void remove(Unit *u);	// Stage������ �ҷ��� �Ѵ�.

	void processAttack(const AttackData& data);

	std::vector<Unit*>::iterator begin();
	std::vector<Unit*>::iterator end();

protected:
	std::vector<Unit*> members;
};