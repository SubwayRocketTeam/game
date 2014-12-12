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

	void push(Unit *u);		// Stage에서만 불러야 한다.
	void remove(Unit *u);	// Stage에서만 불러야 한다.

	void processAttack(const AttackData& data);

	std::vector<Unit*>::iterator begin();
	std::vector<Unit*>::iterator end();

protected:
	std::vector<Unit*> members;
};