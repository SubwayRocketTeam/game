#pragma once

#include "cocos2d.h"

class Player;
class Stage;

class GameScene : public cocos2d::Layer{
public:
	CREATE_FUNC(GameScene);
    virtual bool init();  

    static cocos2d::Scene* scene();

	virtual void update(
		float dt);

private:
	Player *player;
	Stage *stage;
};
