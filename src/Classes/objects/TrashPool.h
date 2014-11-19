#pragma once

#include "Unit.h"

class Trash;

class TrashPool : public cocos2d::Node{
	friend Trash;

public:
	static TrashPool *create();
	static TrashPool *getInstance();

	void spawn(
		int count =0);

	cocos2d::Vector<Trash*> query(
		cocos2d::Rect rect);

protected:
	TrashPool();
	virtual ~TrashPool();

	void push(
		Trash *trash);
	void remove(
		Trash *trash);

	virtual bool init();

	virtual void update(
		float dt);

private:
	cocos2d::Vector<Trash*> trashes;
};
