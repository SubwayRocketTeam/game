#include "pch.h"
#include "MouseEventListener.h"

using namespace cocos2d;

MouseEventListener::MouseEventListener() :
	mouseListener(nullptr){
}
MouseEventListener::~MouseEventListener(){
}

void MouseEventListener::enableMouseInput(
	Node *target){

	mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = [this](Event *event){
		EventMouse *e = (EventMouse*)event;
		onMouseMove(
			e->getMouseButton(),
			e->getCursorX(), e->getCursorY());
	};
	mouseListener->onMouseUp = [this](Event *event){
		EventMouse *e = (EventMouse*)event;
		onMouseDown(
			e->getMouseButton(),
			e->getCursorX(), e->getCursorY());
	};
	mouseListener->onMouseDown = [this](Event *event){
		EventMouse *e = (EventMouse*)event;
		onMouseUp(
			e->getMouseButton(),
			e->getCursorX(), e->getCursorY());
	};

	target->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(mouseListener, target);
}
void MouseEventListener::disableMouseInput(){
	if(mouseListener){
		target->getEventDispatcher()->
			removeEventListener(mouseListener);
	}
}

void MouseEventListener::onMouseMove(
	int btn, float x,float y){

	cocos2d::log("onMouseMove : override me");
}
void MouseEventListener::onMouseDown(
	int btn, float x,float y){

	cocos2d::log("onMouseDown : override me");
}
void MouseEventListener::onMouseUp(
	int btn, float x,float y){

	cocos2d::log("onMouseUp : override me");
}