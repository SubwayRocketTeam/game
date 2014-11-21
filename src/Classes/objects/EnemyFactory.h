#pragma once

#include "cocos2d.h"

#include "EnemyType.h"

#include <map>

class Enemy;
struct EnemyInfo;

class EnemyFactory {
public:
	Enemy* createEnemy(EnemyType type);

	static EnemyFactory* create();
	static EnemyFactory* getInstance();

protected:
	EnemyFactory();
	~EnemyFactory();

	bool init();
	bool initExternalData(const std::string &dataPath);
private:
	std::vector<EnemyInfo*> dic;
};