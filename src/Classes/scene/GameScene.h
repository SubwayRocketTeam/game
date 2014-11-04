#pragma once

#include "cocos2d.h"

class Player;
class Stage;
class Cursor;

class GameScene : public cocos2d::Scene {
public:
	CREATE_FUNC(GameScene);
    virtual bool init();  

    static cocos2d::Scene* scene();

	virtual void update(
		float dt);

private:
	Player *player;
	Stage *stage;
	Cursor *cursor;
};
