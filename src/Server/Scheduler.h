#pragma once

#include "IDDispenser.h"

typedef concurrency::concurrent_queue<id_t> ScheduleQueue;

class Scheduler {
public:
	static void create();
	static Scheduler* getInstance();

	void schedule(id_t room_id);

private:
	Scheduler();
	~Scheduler();

	void init();

public:
	static HANDLE hCompletionPort;

private:
	std::thread timerThread;
	ScheduleQueue scheduleQueue;

};