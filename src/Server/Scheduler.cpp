#include "stdafx.h"
#include "Scheduler.h"

#include "IOContext.h"
#include "CompletionKeyType.h"
#include "GameRoomManager.h"
#include "Event.h"

struct TimerArg {
	HANDLE timer;
	id_t room_id;
	size_t ref_count;
};

void timerThreadProc(ScheduleQueue* scheduleQueue);
void CALLBACK timerCallback(LPVOID lpArgToCompletionRoutine, DWORD dwTimerLowValue, DWORD dwTimerHighValue);

HANDLE Scheduler::hCompletionPort = INVALID_HANDLE_VALUE;

Scheduler instance;
static std::atomic<bool> scheduleOver = false;

Scheduler* Scheduler::getInstance() {
	return &instance;
}

Scheduler::~Scheduler() {
	scheduleOver = true;
	SetEvent(Event::newSchedule);
	timerThread.join();
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
	period.QuadPart = -160000;

	while (true) {
		WaitForSingleObjectEx(Event::newSchedule, INFINITE, TRUE);

		if (scheduleOver)
			break;

		while (!scheduleQueue->empty()) {
			HANDLE timer = CreateWaitableTimer(NULL, TRUE, NULL);
			TimerArg* schedulerArg = new TimerArg();
			schedulerArg->timer = timer;
			schedulerArg->ref_count = 1;
			while (scheduleQueue->try_pop(schedulerArg->room_id));
			// SetWaitableTimer(timer, &period, 16, timerCallback, schedulerArg, FALSE);
			SetWaitableTimer(timer, &period, 0, timerCallback, schedulerArg, FALSE);
		}
	}
}

void CALLBACK timerCallback(LPVOID lpArgToCompletionRoutine, DWORD dwTimerLowValue, DWORD dwTimerHighValue) {
	LARGE_INTEGER period = { 0, };
	period.QuadPart = -160000;

	TimerArg* schedulerArg = (TimerArg*)lpArgToCompletionRoutine;
	schedulerArg->ref_count -= 1;

	TimerContext* context = new TimerContext();
	context->gameRoomId = schedulerArg->room_id;

	/* ISSUE : 게임 룸 컨테이너에 대한 레이스컨디션 */
	if (GameRoomManager::getInstance()->getGameRoom(schedulerArg->room_id)) {
		PostQueuedCompletionStatus(Scheduler::hCompletionPort, 0, CKT_TIMER, (LPOVERLAPPED)context);
		// schedulerArg->tick = timeGetTime();
		// SetWaitableTimer(schedulerArg->timer, &period, 16, timerCallback, lpArgToCompletionRoutine, TRUE);
		schedulerArg->ref_count += 1;
		SetWaitableTimer(schedulerArg->timer, &period, 0, timerCallback, lpArgToCompletionRoutine, TRUE);
	}
	else if (schedulerArg->ref_count == 0) {
		CloseHandle(schedulerArg->timer);
		SAFE_DELETE(schedulerArg);
	}
}