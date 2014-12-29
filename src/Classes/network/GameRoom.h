#pragma once

class GameRoom {
public:
	struct Client {
		int id = 0;
		std::string nickname;
		int team = 0;
		int robot = 0;
		bool ready = false;
	};

	static GameRoom* create();
	static GameRoom* getInstance();

	void setRoomId(int room_id);
	int getRoomId();

	void setMyId(int my_id);
	int getMyId();

	void setWinTeam(int team_id);
	int getWinTeam();

	void addClient(const Client& client);
	void removeClient(int id);
	Client& getClient(int id);

	std::map<int, Client>::const_iterator begin() const;
	std::map<int, Client>::const_iterator end() const;

	void clear();

private:
	GameRoom();
	~GameRoom();

	bool init();

private:
	int roomId;
	int myId;
	int winTeam;
	std::map<int, Client> clients;

};