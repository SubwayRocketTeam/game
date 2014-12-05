#include "stdafx.h"
#include "GameRoomManager.h"
#include "GameRoom.h"
#include "Scheduler.h"

/* ISSUE : 이러면 생성자 무조건 public으로 놔야됨 */
GameRoomManager instance;

GameRoomManager::GameRoomManager() :
	available(nullptr){
}

GameRoomManager* GameRoomManager::getInstance() {
	return &instance;
}


GameRoom* GameRoomManager::getGameRoom(const id_t id) {
	std::lock_guard<std::mutex> lock(mutex);
	auto it = rooms.find(id);
	if (it == rooms.end())
		return nullptr;
	return it->second;
}
GameRoom *GameRoomManager::getAvailableGameRoom(){
	/* TODO : 4 교체 */
	if(available->clientIds.size() >= 4)
		available = nullptr;

	if(available == nullptr){
		/* ISSUE : id로 관리하면 매번 map::find가 실행됨 */ 
		/* SOLUTION : createGameRoom이 GameRoom*을 반환하게 */
		available = 
			getGameRoom(createGameRoom());
	}

	return available;
}

id_t GameRoomManager::createGameRoom() {
	std::lock_guard<std::mutex> lock(mutex);
	id_t id = dispenser.issue();
	GameRoom* room = new GameRoom(id);
	rooms[id] = room;
	Scheduler::getInstance()->schedule(id);
	return id;
}

bool GameRoomManager::removeGameRoom(const id_t id) {
	std::lock_guard<std::mutex> lock(mutex);
	auto it = rooms.find(id);
	if (it == rooms.end())
		return false;
	rooms.erase(it);
	return true;
}
