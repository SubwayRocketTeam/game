#pragma once

struct Attributes
{
	Attributes();

	// Max HP
	// Addition
	int maxHp;
	// Max MP
	// Addition
	int maxMp;

	// Now HP
	int nowHp;
	// Now MP
	int nowMp;

	// HP regen per second
	// Addition
	int hpRegen;
	// MP regen per second
	// Addition
	int mpRegen;

	// Attack point
	// Addition
	int attack;
	// Defence point
	// Addition
	int defence;

	// Attack delay (seconds)
	// Addition
	float attackDelay;
	// Move speed (pixel per second)
	// Addition
	float moveSpeed;

	// Critical attack rate [0, 1]
	// Multiplication
	float criticalRate;
	// Hit rate [0, 1]
	// Multiplication
	float hitRate;
	// Evade rate [0, 1]
	// Multiplication
	float evadeRate;
};