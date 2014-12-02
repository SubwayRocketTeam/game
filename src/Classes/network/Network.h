﻿#pragma once

#include <string>
#include <thread>
#include <functional>
#include <map>

#include <WinSock2.h>
#include <Windows.h>

#include "Packet.h"

class Network{
public:
	typedef std::function<void(int)> OpenHandler;

public:
	static Network *create();
	static Network *getInstance();

	void open(
		const std::string &host, int port,
		OpenHandler handler);
	void close();

	void sendSecHello();
	void sendSecSessionKey(
		int n, int pub_key);
	void sendLoginRequest(
		const char *user_id, const char *user_pw);
	void sendMoveStart(
		float direction_x, float direction_y);
	void sendMoveEnd(
		float delta);
	void sendEnterRoom();
	void sendLeaveRoom();
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

	void handleSecPubKey(
		SecPubKey *pkt);
	void handleEnterRoomNoti(
		EnterNoti *pkt);
	void handleLeaveRoomNoti(
		LeaveNoti *pkt);
	void handleSpawn(
		SpawnUnit *pkt);
	void handleMoveStart(
		MoveStartNoti *pkt);
	void handleMoveEnd(
		MoveEndNoti *pkt);
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
		packet_header* arg){

		f((T*)arg);	
	}

private:
	std::thread *trd;
	std::map<int,std::function<void(packet_header*)>> handlers;

	SOCKET sock;

	bool ssl_ready;
	int enc_key;
	int dec_key;
	int enc_n;
	int dec_n;
};