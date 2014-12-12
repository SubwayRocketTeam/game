#pragma once

#include "EnemyType.h"

class Enemy;
struct EnemyInfo;

class EnemyFactory {
public:
	EnemyFactory();
	~EnemyFactory();

	bool init();
	bool initExternalData(const std::string &dataPath);

	static EnemyFactory* getInstance();
	Enemy* createEnemy(EnemyType type);

private:
	std::vector<EnemyInfo*> dic;
};