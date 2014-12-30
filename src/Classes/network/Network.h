#pragma once

#include <string>
#include <thread>
#include <functional>
#include <map>

#include <WinSock2.h>
#include <Windows.h>

#include "Packet.h"

class NetworkSender{
};
class NetworkHandler{
};

class Network{
public:
	typedef std::function<void(int)> OpenHandler;

public:
	static Network *create();
	static void purge();
	static Network *getInstance();

	void open(
		const std::string &host, int port,
		OpenHandler handler);
	void close();

	bool isConnected();

	void sendLoginRequest(
		const char *nickname);
	void sendMove(
		float direction_x, float direction_y);
	void sendSyncRotation(
		float angle);

	void sendRoomRequest();
	void sendEnterRoom(
		int room_id);
	void sendLeaveRoom();

	void sendSelectRobot(
		int robot_id);
	void sendSelectTeam(
		int team_id);
	void sendReadyRequest(
		bool ready);

	void sendSpawnRequest(
		int unitType);

	void sendUseSkill(
		int skillID,
		float x,float y);

	void sendUpgrade(
		UpgradeType upgradeType);

	void sendChatMessage(
		const char *msg);

	template <typename T>
	void route(
		int pid,
		std::function<void(T*)> callback){

		handlers[pid] = std::bind(
			&Network::invoker<T>,
			this,
			callback, std::placeholders::_1);
	};

protected:
	Network();
	virtual ~Network();

	void initHandlers();

	void handleLoginResponse(
		LoginResponse *pkt);

	void handleRoomResponse(
		RoomResponse *pkt);
	void handleEnterResponse(
		EnterResponse *pkt);
	void handleEnterNoti(
		EnterNoti *pkt);
	void handleLeaveNoti(
		LeaveNoti *pkt);
	void handleSelectRobotNoti(
		SelectRobotNoti *pkt);
	void handleSelectTeamNoti(
		SelectTeamNoti *pkt);
	void handleReadyNoti(
		ReadyNoti *pkt);
	void handleStartGame(
		StartGame *pkt);
	void handleGameOver(
		GameOver *pkt);
	void handleSpawn(
		SpawnUnit *pkt);
	void handleRemoveUnit(
		RemoveUnit *pkt);
	void handleSetPhysics(
		SetPhysics *pkt);

	void handleUseSkillNoti(
		UseSkillNoti *pkt);
	void handleUpgrade(
		UpgradeNoti *pkt);
	void handleAddPassiveNoti(
		AddPassiveNoti *pkt);
	void handleRemovePassiveNoti(
		RemovePassiveNoti *pkt);
	void handleAttack(
		Attack *pkt);

	void handleMove(
		MoveNoti *pkt);
	void handleSyncRotationNoti(
		SyncRotationNoti *pkt);
	void handleVacuum(
		Vacuum *pkt);

	void handleChatNoti(
		ChatNoti *pkt);

	int recv(
		void *dst, int len);
	int send(
		void *src, int len);

	template <typename T>
	int send(
		T &packet){
		return send(&packet, sizeof(packet));
	}

	void worker(
		const std::string &host, int port,
		OpenHandler handler);
	void recvLoop();

	void throwTaskToGameThread(
		std::function<void()> task);

	template <typename T>
	void invoker(
		std::function<void(T*)> f,
		PacketHeader* arg){

		f((T*)arg);
		free(arg);
	}

private:
	std::thread *trd;
	std::map<int,std::function<void(PacketHeader*)>> handlers;

	SOCKET sock;

	bool connected;
};