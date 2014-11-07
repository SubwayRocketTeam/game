#pragma once

#include "cocos2d.h"

#include "objects/KeyboardEventListener.h"

class Player;
class Stage;
class Cursor;
class UserResources;

class GameScene : public cocos2d::Layer,
	public KeyboardEventListener{
public:
	CREATE_FUNC(GameScene);
    virtual bool init();  

    static cocos2d::Scene* scene();

	virtual void update(
		float dt);

protected:
	virtual void onKeyboardDown(
		cocos2d::EventKeyboard::KeyCode keycode);

private:
	Player *player;
	Stage *stage;
	Cursor *cursor;
};
