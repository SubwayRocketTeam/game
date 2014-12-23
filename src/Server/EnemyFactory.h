#pragma once

#include "EnemyType.h"

class Enemy;
struct EnemyInfo;

class EnemyFactory {
public:
	static void create();
	static EnemyFactory* getInstance();

	Enemy* createEnemy(EnemyType type);
	EnemyInfo* getEenmyInfo(EnemyType type);

private:
	EnemyFactory();
	~EnemyFactory();

	bool init();
	bool initExternalData(const std::string &dataPath);

private:
	std::vector<EnemyInfo*> dic;
};