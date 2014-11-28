#pragma once

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

	void sendLoginRequest(
		STRING(user_id), STRING(user_pw));

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
};