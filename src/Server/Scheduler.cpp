#include "stdafx.h"
#include "Scheduler.h"

#include "IOContext.h"
#include "CompletionKeyType.h"
#include "GameRoomManager.h"
#include "Event.h"

struct TimerArg {
	HANDLE timer;
	id_t room_id;
	DWORD tick;
};

void timerThreadProc(ScheduleQueue* scheduleQueue);
void CALLBACK timerCallback(LPVOID lpArgToCompletionRoutine, DWORD dwTimerLowValue, DWORD dwTimerHighValue);

HANDLE Scheduler::hCompletionPort = INVALID_HANDLE_VALUE;

Scheduler instance;


Scheduler* Scheduler::getInstance() {
	return &instance;
}

Scheduler::Scheduler() {

}

void Scheduler::init() {
	timerThread = std::thread(timerThreadProc, &scheduleQueue);
}

void Scheduler::schedule(id_t room_id) {
	scheduleQueue.push(room_id);
	SetEvent(Event::newSchedule);
}


void timerThreadProc(ScheduleQueue* scheduleQueue){
	LARGE_INTEGER period = { 0, };

	while (true) {
		WaitForSingleObjectEx(Event::newSchedule, INFINITE, TRUE);
		while (!scheduleQueue->empty()) {
			HANDLE timer = CreateWaitableTimer(NULL, TRUE, NULL);
			TimerArg* schedulerArg = new TimerArg();
			schedulerArg->timer = timer;
			while (scheduleQueue->try_pop(schedulerArg->room_id));
			SetWaitableTimer(timer, &period, 16, timerCallback, schedulerArg, TRUE);
		}
		ResetEvent(Event::newSchedule);
	}
}

void CALLBACK timerCallback(LPVOID lpArgToCompletionRoutine, DWORD dwTimerLowValue, DWORD dwTimerHighValue) {
	LARGE_INTEGER period = { 0, };
	TimerArg* schedulerArg = (TimerArg*)lpArgToCompletionRoutine;

	TimerContext* context = new TimerContext();
	context->gameRoomId = schedulerArg->room_id;

	if (GameRoomManager::getInstance()->getGameRoom(schedulerArg->room_id)) {
		PostQueuedCompletionStatus(Scheduler::hCompletionPort, 0, CKT_TIMER, (LPOVERLAPPED)context);
		schedulerArg->tick = timeGetTime();
		SetWaitableTimer(schedulerArg->timer, &period, 16, timerCallback, lpArgToCompletionRoutine, TRUE);
	}
	else {
		CloseHandle(schedulerArg->timer);
		SAFE_DELETE(schedulerArg);
	}
}