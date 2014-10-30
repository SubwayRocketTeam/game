#pragma once

#include "cocos2d.h"

#include <vector>

class Enemy;

class EnemyPool : public cocos2d::Node{
public:
	static EnemyPool *create();
	static EnemyPool *getInstance();

    virtual bool init();

	void push(
		Enemy *e);
	void remove(
		Enemy *e);

	void focus(
		Enemy *e);

protected:
	EnemyPool();
	virtual ~EnemyPool();
};
