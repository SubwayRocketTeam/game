#include "pch.h"
#include "GameRoom.h"


static GameRoom* instance;
static GameRoom::Client nullClient;

GameRoom* GameRoom::create() {
	instance = new GameRoom();
	instance->init();
	return instance;
}
GameRoom* GameRoom::getInstance() {
	return instance;
}

void GameRoom::setRoomId(int room_id) {
	roomId = room_id;
}
int GameRoom::getRoomId() {
	return roomId;
}

void GameRoom::setMyId(int my_id) {
	myId = my_id;
}
int GameRoom::getMyId() {
	return myId;
}

void GameRoom::setWinTeam(int team_id) {
	winTeam = team_id;
}
int GameRoom::getWinTeam() {
	return winTeam;
}


void GameRoom::addClient(const Client& client) {
	clients[client.id] = client;
}
void GameRoom::removeClient(int id) {
	clients.erase(id);
}
GameRoom::Client& GameRoom::getClient(int id) {
	auto it = clients.find(id);
	if (it == clients.end())
		return nullClient;
	return it->second;
}

GameRoom::GameRoom() :roomId(0), myId(0), winTeam(0) {

}
GameRoom::~GameRoom() {

}

bool GameRoom::init() {
	return true;
}

std::map<int, GameRoom::Client>::const_iterator GameRoom::begin() const {
	return clients.begin();
}

std::map<int, GameRoom::Client>::const_iterator GameRoom::end() const {
	return clients.end();
}


void GameRoom::clear() {
	roomId = 0;
	clients.clear();
}