#include "pch.h"
#include "KeyboardEventListener.h"

using namespace cocos2d;

KeyboardEventListener::KeyboardEventListener() :
	keyboardListener(nullptr){
}
KeyboardEventListener::~KeyboardEventListener(){
}

void KeyboardEventListener::enableKeyboardInput(
	Node *target){

	keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed =
	[this](EventKeyboard::KeyCode keycode, Event *e){
		keymap[keycode] = true;
		onKeyboardDown(keycode);
	};
	keyboardListener->onKeyReleased =
	[this](EventKeyboard::KeyCode keycode, Event *e){
		keymap[keycode] = false;
		onKeyboardUp(keycode);
	};

	auto director = Director::getInstance();
	director->getScheduler()->schedule(
		SEL_SCHEDULE(&KeyboardEventListener::processKeyTurbo), (Ref*)this,
		director->getFrameRate(), false);

	target->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(keyboardListener, target);
}
void KeyboardEventListener::disableKeyboardInput(){
	if(keyboardListener){
		target->getEventDispatcher()->
			removeEventListener(keyboardListener);
	}
}
void KeyboardEventListener::processKeyTurbo(float dt){
	for(auto p : keymap){
		if(p.second == true)
			onKeyboardPressed(p.first);
	}
}

void KeyboardEventListener::onKeyboardDown(
	EventKeyboard::KeyCode keycode){

	cocos2d::log("onKeyboardDown : override me");
}
void KeyboardEventListener::onKeyboardUp(
	EventKeyboard::KeyCode keycode){

	cocos2d::log("onKeyboardUp : override me");
}
void KeyboardEventListener::onKeyboardPressed(
	EventKeyboard::KeyCode keycode){

	cocos2d::log("onKeyboardPressed : override me");
}