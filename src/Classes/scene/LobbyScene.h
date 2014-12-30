#pragma once

#include "cocos2d.h"

#include "editor-support/cocostudio/CCSGUIReader.h"

class LobbyScene : public cocos2d::Layer{
public:
	CREATE_FUNC(LobbyScene);

	static cocos2d::Scene* scene();

	void addRooms(int room_num, char* room_ids);

protected:
	LobbyScene();
	virtual ~LobbyScene();

	virtual bool init();

	void enter(int room_id);
	void refresh();

	virtual void onInitGlobalObjects();
	virtual void onReleaseGlobalObjects();

	virtual void onEnter();

	void onEnterRoom(
		cocos2d::Ref *sender, int room_id);
	void onFastStart(
		cocos2d::Ref *sender);
	void onRefresh(
		cocos2d::Ref *sender);


protected:
	std::vector<int> rooms;
};
