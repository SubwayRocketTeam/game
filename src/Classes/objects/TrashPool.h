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
	void spawn(
		const cocos2d::Vec2 &pos,
		int count = 0);

	cocos2d::Vector<Trash*> query(
		const cocos2d::Rect &rect);

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
