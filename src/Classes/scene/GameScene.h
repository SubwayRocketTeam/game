#pragma once

#include "cocos2d.h"

class Player;
class Stage;
class Cursor;
class UserResources;

class GameScene : public cocos2d::Layer{
public:
	CREATE_FUNC(GameScene);

    static cocos2d::Scene* scene();

protected:
	virtual bool init();
	virtual bool initUI();

	virtual void onEnter();
	virtual void onExit();

	virtual void update(
		float dt);

private:
	Player *player;
	Stage *stage;
	Cursor *cursor;
};
