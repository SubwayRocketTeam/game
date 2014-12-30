#include "stdafx.h"
#include "GameRoom.h"
#include "GameRoomManager.h"
#include "ClientManager.h"
#include "Client.h"
#include "CompletionKeyType.h"
#include "Unit.h"
#include "Enemy.h"
#include "Player.h"
#include "TrashPool.h"
#include "RepairArea.h"

#include "Ally.h"

#include "config.h"

typedef std::pair<id_t, id_t> IdPair;

GameRoom::GameRoom(const id_t id)
	:id(id), gameRunning(false), gameOver(false), gameOverTick(0) {
	for (int i = 0; i < Max::Teams; ++i)
		stage[i] = new Stage(this, i);
	
	stage[0]->oppositStage = stage[1];
	stage[1]->oppositStage = stage[0];
}

GameRoom::~GameRoom() {
	for (Unit* u : units) {
		SAFE_DELETE(u);
	}
	units.clear();

	if (config::gui) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}
}

void GameRoom::update() {

	DWORD now_tick = timeGetTime();

	if (gameRunning) {

		for (int i = 0; i < Max::Teams; ++i)
			stage[i]->update((now_tick - tick) * 0.001f);

		flush();


		if (!gameOver) {
			for (int i = 0; i < Max::Teams; ++i) {
				if (stage[i]->isExterminated()) {
					GameOver noti;
					noti.win_team = _OPPOSITE(i);
					sendPacket(noti);
					gameOver = true;
					gameOverTick = now_tick;
					return;
				}
			}
		}
		else if (now_tick > gameOverTick + config::gameover_time_wait){
			gameRunning = false;
		}

	}

	tick = now_tick;

	if (config::gui) {
		SDL_SetRenderDrawColor(renderer, 255, 2552, 255, 255);
		SDL_RenderClear(renderer);

		for (auto unit : units){
			if (unit->stage->id != 0)
				continue;
			SDL_Rect rect = {
				(200 + unit->position.x / 4) - 5, 300 - (150 + unit->position.y / 4) - 5,
				10, 10 };
			SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
			SDL_RenderFillRect(
				renderer, &rect);
		}
		for (auto player : *stage[0]->ally[0]){
			SDL_Rect rect = {
				(200 + player->position.x / 4) - 6, 300 - (150 + player->position.y / 4) - 6,
				12, 12 };
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderFillRect(
				renderer, &rect);
		}
		for (auto enemy : *stage[0]->ally[1]){
			SDL_Rect rect = {
				(200 + enemy->position.x / 4) - 6, 300 - (150 + enemy->position.y / 4) - 6,
				12, 12 };
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(
				renderer, &rect);
		}

		SDL_RenderPresent(renderer);

		SDL_Event event;
		SDL_PollEvent(&event);
	}
}


bool GameRoom::enter(const id_t client_id) {
	if (client_id == INVALID_ID) return false;
	if (clientIds.size() >= 4) return false;
	if (!clientIds.insert(IdPair(client_id, INVALID_ID)).second)
		return false;
	auto client = ClientManager::getInstance()->getClient(client_id);
	client->gameRoomId = id;
	int team = getTeamNum(0) <= getTeamNum(1) ? 0 : 1;
	teams[client_id] = team;
	readyMap[client_id] = false;

	EnterNoti noti;

	for (auto pair : clientIds) {
		if (pair.first == client_id)
			continue;
		auto other_client = ClientManager::getInstance()->getClient(pair.first);
		noti.client_id = pair.first;
		strcpy_s(noti.nickname, other_client->nickname.c_str());
		noti.team_id = getTeam(pair.first);
		noti.robot_id = other_client->robotType;
		noti.ready = readyMap[pair.first] ? 1 : 0;
		client->sendPacket(noti);
	}

	noti.client_id = client_id;
	strcpy_s(noti.nickname, client->nickname.c_str());
	noti.team_id = team;
	noti.ready = readyMap[client_id] ? 1 : 0;
	noti.robot_id = client->robotType;
	sendPacket(noti);

	return true;
}

bool GameRoom::leave(const id_t client_id) {
	if (client_id == INVALID_ID) return false;
	auto it = clientIds.find(client_id);
	if (it == clientIds.end())
		return false;
	clientIds.erase(it);
	teams.erase(client_id);
	readyMap.erase(client_id);
	ClientManager::getInstance()->getClient(client_id)->gameRoomId = INVALID_ID;

	LeaveNoti noti;
	noti.client_id = client_id;
	sendPacket(noti);

	if (gameRunning) {
		auto player = getClientUnit(client_id);
		if (player) {
			player->stage->removeUnit(player);
			RemoveUnit noti;
			noti.id = player->id;
			sendPacket(noti);
		}
	}

	// 모두 나가면 방폭
	if (clientIds.size() == 0)
		GameRoomManager::getInstance()->removeGameRoom(id);
	return true;
}

bool GameRoom::ready(const id_t client_id, const bool is_ready) {
	if (client_id == INVALID_ID) return false;
	auto it = clientIds.find(client_id);
	if (it == clientIds.end())
		return false;
	if (readyMap[client_id] == is_ready)
		return false;

	readyMap[client_id] = is_ready;

	ReadyNoti noti;
	noti.client_id = client_id;
	noti.ready = is_ready ? 1 : 0;
	sendPacket(noti);

	if (isAllReady() && getTeamNum(0) == getTeamNum(1))
		startGame();
	return true;
}


bool GameRoom::startGame() {
	if (gameRunning) return false;
	gameRunning = true;

	StartGame packet;
	sendPacket(packet);

	for (auto& id : clientIds) {
		Client* client = ClientManager::getInstance()->getClient(id.first);
		Player* player = new Player();
		player->init(client->robotType);
		id.second = stage[teams[id.first]]->addUnit(player);

		// TODO: 위치 지정
		player->position.x = (float)(rand() % 1600 - 800);
		player->position.y = (float)(rand() % 1200 - 600);

		SpawnUnit noti;
		noti.id = id.second;
		noti.stage = player->stage->id;
		noti.unit_type = UNIT_PLAYER_ME;
		noti.sub_type = client->robotType;
		noti.x = player->position.x;
		noti.y = player->position.y;
		client->sendPacket(noti);
	}

	flush();

	for (auto id : clientIds) {
		Player* player = (Player*)getUnit(id.second);
		SpawnUnit noti;
		noti.id = id.second;
		noti.stage = player->stage->id;
		noti.unit_type = UNIT_PLAYER;
		noti.sub_type = player->getPlayerType();
		noti.x = player->position.x;
		noti.y = player->position.y;
		sendPacket(noti);
	}

	for (int i = 0; i < Max::Teams; ++i) {
		// Repair Area 스폰
		SpawnUnit noti;
		noti.id = stage[i]->repairArea->id;
		noti.stage = i;
		noti.unit_type = UNIT_REPAIR_AREA;
		noti.x = stage[i]->repairArea->position.x;
		noti.y = stage[i]->repairArea->position.y;
		sendPacket(noti);

		// 쓰레기 뿌리기
		stage[i]->trashPool->spawn(clientIds.size() * config::start_trash);
	}

	if (config::gui) {
		window = SDL_CreateWindow(
			"dbgwindow",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			400, 300, 0);
		renderer = SDL_CreateRenderer(
			window, -1, 0);
	}

	return true;
}


id_t GameRoom::addUnit(Unit* unit) {
	if (!unit)
		return INVALID_ID;
	if (!addUnits.insert(unit).second)
		return unit->id;
	id_t id = dispenser.issue();
	unit->id = id;
	return id;
}

void GameRoom::removeUnit(Unit* unit) {
	if (!unit) return;
	removeUnits.insert(unit);
}

void GameRoom::addUnitImmediate(Unit* unit) {
	if (!unit) return;
	
	auto it = std::find(units.begin(), units.end(), unit);
	if (it != units.end())
		return;

	units.push_back(unit);
	unit->stage->addUnitImmediate(unit);

	/*
	SpawnUnit noti;
	noti.id = unit->id;
	noti.unit_type = unit->type;
	if (unit->type == UT_ENEMY) {
		Enemy* enemy = (Enemy*)unit;
		noti.unit_type = 10 + enemy->getEnemyType();
	}
	noti.x = unit->position.x;
	noti.y = unit->position.y;
	sendPacket(noti);
	*/
}

void GameRoom::removeUnitImmediate(Unit* unit) {
	if (!unit) return;

	auto it = std::find(units.begin(), units.end(), unit);
	if (it == units.end())
		return;

	unit->stage->removeUnitImmediate(unit);
	units.erase(it);
	SAFE_DELETE(unit);
}

void GameRoom::flush() {
	for (Unit* u : removeUnits)
		removeUnitImmediate(u);
	removeUnits.clear();

	for (Unit* u : addUnits)
		addUnitImmediate(u);
	addUnits.clear();

}

Unit* GameRoom::getUnit(const id_t id) {
	auto it = std::find_if(units.begin(), units.end(), [id](Unit* u){ return u->id == id; });
	if (it == units.end())
		return nullptr;
	return *it;
}

Unit* GameRoom::getClientUnit(const id_t client_id) {
	return getUnit(GameRoom::getClientUnitId(client_id));
}

id_t GameRoom::getClientUnitId(const id_t client_id) {
	auto it = clientIds.find(client_id);
	if (it == clientIds.end())
		return INVALID_ID;
	return it->second;
}

void GameRoom::setTeam(const id_t client_id, int team) {
	auto it = teams.find(client_id);
	if (it == teams.end())
		return;
	it->second = team;

	SelectTeamNoti noti;
	noti.client_id = client_id;
	noti.team_id = team;
	sendPacket(noti);
}


int GameRoom::getTeam(const id_t client_id) {
	auto it = teams.find(client_id);
	if (it == teams.end())
		return -1;
	return it->second;
}

int GameRoom::getTeamNum(const int team_id) {
	return std::count_if(teams.begin(), teams.end(), [team_id](const std::pair<id_t, int>& pair){return pair.second == team_id; });
}



size_t GameRoom::getClientNum() const {
	return clientIds.size();
}


int GameRoom::send(void* const buf, const size_t size) {
	if (!buf || size < 1)
		return SOCKET_ERROR;
	for (auto id : clientIds) {
		Client* client = ClientManager::getInstance()->getClient(id.first);
		if (client)
		{
			if (client->send(buf, size) == SOCKET_ERROR)
				return SOCKET_ERROR;
		}
	}
	return 0;
}


IdPairMap::const_iterator GameRoom::begin() const {
	return clientIds.begin();
}

IdPairMap::const_iterator GameRoom::end() const {
	return clientIds.end();
}

bool GameRoom::empty() const {
	return clientIds.empty();
}

size_t GameRoom::size() const {
	return clientIds.size();
}

bool GameRoom::isPlaying() {
	return gameRunning || gameOver;
}

bool GameRoom::isFull() {
	return clientIds.size() >= 4;
}

bool GameRoom::isAllReady() {
	for (auto pair : readyMap) {
		if (!pair.second)
			return false;
	}
	return true;
}