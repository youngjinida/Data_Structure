#include "Multi_thread.h"
#include "Event.h"
#include "HeapPrioQ.h"
#define myExitCode 0

unsigned _stdcall Thread_EventGenerator(LPVOID pParam)
{
	ThreadParam_Event* pThrdParam;
	HeapPrioQueue<int, Event>* pPrioQ_Event;
	int myRole;
	THREAD_FLAG* pFlagThrdTerminate;
	int maxRound;
	T_Entry<int, Event>* pEntry, entry_event;
	Event event;
	Event* pEvent;
	int evt_no = 0;
	int evt_prio = 0;
	int event_gen_cnt = 0;
	int targetEventGen;
	int myAddr;
	int event_handler_addr;
	LARGE_INTEGER QP_freq, t_gen;
	ThreadStatusMonitor* pThreadMon;
	pThrdParam = (ThreadParam_Event*)pParam;
	myRole = pThrdParam->role;
	myAddr = pThrdParam->myAddr;
	maxRound = pThrdParam->maxRound;
	pPrioQ_Event = pThrdParam->pPriQ_Event;
	pThreadMon = pThrdParam->pThrdMon;
	targetEventGen = pThrdParam->targetEventGen;

	for (int round = 0; round < maxRound; ++round)
	{
		if (event_gen_cnt >= targetEventGen)
		{
			if (*pThreadMon->pFlagThreadTerminate == TERMINATE)
				break;
			else
			{
				Sleep(500);
				continue;
			}
		}
		evt_no = event_gen_cnt + NUM_EVENTS_PER_GEN * myAddr;
		evt_prio = targetEventGen - event_gen_cnt - 1;
		event.setEventNo(evt_no);
		event.setEventPriority(evt_prio);
		event.setEventGenAddr(myAddr);
		event.setEventHandlerAddr(-1);
		QueryPerformanceCounter(&t_gen);
		event.setEventGenTime(t_gen);
		event.setEventStatus(GENERATED);
		entry_event.setKey(event.getEventPri());
		entry_event.setValue(event);
		while (pPrioQ_Event->insert(entry_event) == NULL)
			Sleep(50);
		EnterCriticalSection(pThrdParam->pCS_thrd_mon);
		pThreadMon->eventGenerated[pThreadMon->totalEventGenerated] = event;
		pThreadMon->numEventGenerated++;
		pThreadMon->totalEventGenerated++;
		LeaveCriticalSection(pThrdParam->pCS_thrd_mon);
		event_gen_cnt++;
		Sleep(10);
	}
	_endthreadex(myExitCode);
	return 0;
}