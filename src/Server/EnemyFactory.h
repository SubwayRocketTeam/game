#pragma once

#include "EnemyType.h"

class Enemy;
struct EnemyInfo;

class EnemyFactory {
public:
	static EnemyFactory* getInstance();
	Enemy* createEnemy(EnemyType type);


protected:
	EnemyFactory();
	~EnemyFactory();

	bool init();
	bool initExternalData(const std::string &dataPath);

private:
	std::vector<EnemyInfo*> dic;
};