#include <Windows.h>
#include "Multi_thread.h"
#include "HeapPrioQ.h"
#include "Event.h"
#define myExitCode 0

unsigned _stdcall Thread_EventHandler(LPVOID pParam)
{
	ThreadParam_Event* pThrdParam;
	HeapPrioQueue<int, Event>* pPriQ_Event;
	int myRole, myAddr, maxRound;
	THREAD_FLAG* pFlagThreadTerminate;
	T_Entry<int, Event>* pEntry;
	Event event;
	Event* pEvent, *pEventProc;
	LARGE_INTEGER QP_freq, t_gen, t_proc;
	LONGLONG t_diff;
	double elapsed_time;
	ThreadStatusMonitor* pThrdMon;

	pThrdParam = (ThreadParam_Event*)pParam;
	myRole = pThrdParam->role;
	myAddr = pThrdParam->myAddr;
	pPriQ_Event = pThrdParam->pPriQ_Event;
	pThrdMon = pThrdParam->pThrdMon;
	maxRound = pThrdParam->maxRound;
	QP_freq = pThrdParam->QP_freq;


	for (int round = 0; round < maxRound; ++round)
	{
		if ((*pThrdMon->pFlagThreadTerminate == TERMINATE))
			break;
		if (!pPriQ_Event->isEmpty())
		{
			pEntry = pPriQ_Event->removeHeapMin();
			event = pEntry->getValue();
			EnterCriticalSection(pThrdParam->pCS_thrd_mon);
			event.setEventHandlerAddr(myAddr);
			QueryPerformanceCounter(&t_proc);
			event.setEventProcTime(t_proc);
			t_gen = event.getEventGenTime();
			t_diff = t_proc.QuadPart - t_gen.QuadPart;
			elapsed_time = ((double)t_diff / QP_freq.QuadPart);
			event.setEventElapsedTime(elapsed_time * 1000);
			pThrdMon->eventProcessed[pThrdMon->totalEventProcessed] = event;
			pThrdMon->numEventProcessed++;
			pThrdMon->totalEventProcessed++;
			LeaveCriticalSection(pThrdParam->pCS_thrd_mon);
		}
		Sleep(100 + rand()%100);
	}
	_endthreadex(myExitCode);
	return 0;
}