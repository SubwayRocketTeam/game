#pragma once

#include "IDDispenser.h"

typedef concurrency::concurrent_queue<id_t> ScheduleQueue;

class Scheduler {
public:
	static Scheduler* getInstance();

	Scheduler();
	void init();

	void schedule(id_t room_id);

public:
	static HANDLE hCompletionPort;

private:
	std::thread timerThread;
	ScheduleQueue scheduleQueue;

};