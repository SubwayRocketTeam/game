#pragma once

#include "Unit.h"

class Trash;

class TrashPool : public cocos2d::Ref{
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

private:
	cocos2d::Vector<Trash*> trashes;
};
