#pragma once

#include "cocos2d.h"

#include <vector>
#include <list>

class StatusConsole : public cocos2d::Sprite{
public:
	static const int MaxLines = 5;
	static const int LineSize = 30;

public:
	static StatusConsole* create();
	static StatusConsole* getInstance();

	void output(
		const std::string &msg);

protected:
	StatusConsole();
	virtual ~StatusConsole();

	virtual bool init();

	void shift();
	void addLine(
		const std::string &msg);

private:
	std::list<cocos2d::LabelTTF*> lines;
};