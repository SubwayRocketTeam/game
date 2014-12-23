#pragma once

#include "cocos2d.h"

#include "EnemyType.h"

#include <map>

class Enemy;
struct EnemyInfo;

class EnemyFactory {
public:
	static EnemyFactory* create();
	static EnemyFactory* getInstance();

	Enemy* createEnemy(
		EnemyType type);
	void spawn(
		EnemyType type);
	EnemyInfo* getEenmyInfo(
		EnemyType type);

protected:
	EnemyFactory();
	~EnemyFactory();

	bool init();
	bool initExternalData(const std::string &dataPath);

private:
	std::vector<EnemyInfo*> dic;
};