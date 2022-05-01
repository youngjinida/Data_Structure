#include <iostream>
#include <conio.h>
#include "ConsoleDisplay.h"
#include "Multi_thread.h"
#include "HeapPrioQ.h"
#include "Event.h"
#include "SimParams.h"

int main()
{
	LARGE_INTEGER QP_freq, t_before, t_after;
	LONGLONG t_diff;
	double elapsed_time, min_elapsed_time, max_elapsed_time;
	double avg_elapsed_time, total_elapsed_time;
	HeapPrioQueue<int, Event> heapPriQ_Event(50, string("HeapPriorityQueue_Event"));
	Event* pEvent, * pEvt_min_elapsed_time = NULL, * pEvt_max_elapsed_time = NULL;
	
	int myAddr = 0;
	int pkt_event_handler_addr, event_priority;
	ThreadParam_Event thrdParam_EventGen, thrdParam_EventHndlr;
	HANDLE hThrd_EventGenerator, hThrd_EventHandler;
	HANDLE consHndlr;
	CRITICAL_SECTION cs_main;
	CRITICAL_SECTION cs_thrd_mon;
	ThreadStatusMonitor thrdMon;
	THREAD_FLAG eventThreadFlag = RUN;
	int cnt, numEventGenerated, numEventProcessed;
	int num_events_in_PrioQ;
	Event eventProcessed[TOTAL_NUM_EVENTS];

	heapPriQ_Event.initCS(&cs_thrd_mon);
	InitializeCriticalSection(&cs_main);
	InitializeCriticalSection(&cs_thrd_mon);
	consHndlr = initConsoleHandler();
	QueryPerformanceFrequency(&QP_freq);
	srand(time(NULL));
	thrdMon.pFlagThreadTerminate = &eventThreadFlag;
	thrdMon.totalEventGenerated = 0;
	thrdMon.totalEventProcessed = 0;

	for (int idx = 0; idx < TOTAL_NUM_EVENTS; ++idx)
	{
		thrdMon.eventProcessed[idx].setEventNo(-1);
		thrdMon.eventProcessed[idx].setEventPriority(-1);
	}

	/* Creative and Activate Thread_EventHandler */
	
	thrdMon.numEventProcessed = 0;
	thrdParam_EventHndlr.role = EVENT_HANDLER;
	thrdParam_EventHndlr.myAddr = 1;
	thrdParam_EventHndlr.pCS_main = &cs_main;
	thrdParam_EventHndlr.pCS_thrd_mon = &cs_thrd_mon;
	thrdParam_EventHndlr.pPriQ_Event = &heapPriQ_Event;
	thrdParam_EventHndlr.maxRound = MAX_ROUND;
	thrdParam_EventHndlr.QP_freq = QP_freq;
	thrdParam_EventHndlr.pThrdMon = &thrdMon;

	hThrd_EventHandler = (HANDLE)_beginthreadex(NULL, 0, Thread_EventHandler,
		&thrdParam_EventHndlr, 0, NULL);
	EnterCriticalSection(&cs_main);
	cout << "Thread_EventHandler is Create and actived .. \n";
	LeaveCriticalSection(&cs_main);

	thrdMon.numEventGenerated = 0;
	thrdParam_EventGen.role = EVENT_GENERATOR;
	thrdParam_EventGen.myAddr = 0;
	thrdParam_EventGen.pCS_main = &cs_main;
	thrdParam_EventGen.pCS_thrd_mon = &cs_thrd_mon;
	thrdParam_EventGen.pPriQ_Event = &heapPriQ_Event;
	thrdParam_EventGen.targetEventGen = NUM_EVENTS_PER_GEN;
	thrdParam_EventGen.maxRound = MAX_ROUND;
	thrdParam_EventGen.QP_freq = QP_freq;
	thrdParam_EventGen.pThrdMon = &thrdMon;
	hThrd_EventGenerator = (HANDLE)_beginthreadex(NULL, 0, Thread_EventGenerator,
		&thrdParam_EventGen, 0, NULL);
	
	EnterCriticalSection(&cs_main);
	cout << "Thread_EventGen is created and actived ...\n";
	LeaveCriticalSection(&cs_main);

	for (int round = 0; round < MAX_ROUND; ++round)
	{
		EnterCriticalSection(&cs_main);
		system("cls");
		gotoxy(consHndlr, 0, 0);
		cout << "Thread monitoring by main() ::\n";
		cout << " round(" << round << "): ";
		cout << "current_total_gen (" << thrdMon.totalEventGenerated << ")";
		cout << " current_total_proc (" << thrdMon.totalEventProcessed << ")\n";
		cout << "\n*********************************\n";
		numEventGenerated = thrdMon.numEventGenerated;
		cout << "Event generated (current total = " << numEventGenerated << ")\n";
		cnt = 0;
		for (int idx = 0; idx < numEventGenerated; ++idx)
		{
			pEvent = &thrdMon.eventGenerated[idx];
			if (pEvent != NULL)
			{
				cout << *pEvent << "";
				if (((idx + 1) % EVENT_PER_LINE) == 0)
					cout << "\n";
			}
		}
		cout << "\n";
		cout << "\n*********************************\n";
		num_events_in_PrioQ = heapPriQ_Event.size();
		cout << "Event currently in Priority_Queue(" << num_events_in_PrioQ << "): \n";
		heapPriQ_Event.fprintHeapQ(cout);

		cout << "\n\n*********************************\n";
		numEventProcessed = thrdMon.totalEventProcessed;
		cout << "Event processed(current total = " << numEventProcessed << "): \n";
		cnt = 0;
		total_elapsed_time = .0;
		for (int idx = 0; idx < numEventProcessed; ++idx)
		{
			pEvent = &thrdMon.eventProcessed[idx];
			if (pEvent != NULL)
			{
				pEvent->printEvent_Proc(cout);
				if ((idx + 1) % EVENT_PER_LINE == 0)
					cout << "\n";
			}
			if (idx == 0)
			{
				min_elapsed_time = max_elapsed_time = total_elapsed_time =
					pEvent->getEventElapsedTime();
				pEvt_min_elapsed_time = pEvt_max_elapsed_time = pEvent;
			}
			else
			{
				if (min_elapsed_time > pEvent->getEventElapsedTime())
				{
					min_elapsed_time = pEvent->getEventElapsedTime();
					pEvt_min_elapsed_time = pEvent;
				}

				if (max_elapsed_time < pEvent->getEventElapsedTime())
				{
					max_elapsed_time = pEvent->getEventElapsedTime();
					pEvt_max_elapsed_time = pEvent;
				}
				total_elapsed_time += pEvent->getEventElapsedTime();
			}
		}
		if (numEventProcessed > 0)
		{
			cout << "\nmin_elapsed_time = " << min_elapsed_time << "[ms]: ";
			cout << *pEvt_min_elapsed_time;
			cout << "\nmax_elapsed_time = " << max_elapsed_time << "[ms]: ";
			cout << *pEvt_max_elapsed_time;
			avg_elapsed_time = total_elapsed_time / numEventProcessed;
			cout << "\navg_elapsed_time = " << avg_elapsed_time << "[ms]: ";
		}
		if (numEventProcessed >= TOTAL_NUM_EVENTS)
		{
			eventThreadFlag = TERMINATE;
			break;
		}
		LeaveCriticalSection(&cs_main);
		Sleep(100);
	}

	DWORD nExitCode = NULL;

	WaitForSingleObject(hThrd_EventGenerator, INFINITE);
	EnterCriticalSection(&cs_main);
	cout << "Thread_EventGenerator is terminated !!\n";
	LeaveCriticalSection(&cs_main);
	GetExitCodeThread(hThrd_EventGenerator, &nExitCode);
	CloseHandle(hThrd_EventGenerator);

	WaitForSingleObject(hThrd_EventHandler, INFINITE);
	EnterCriticalSection(&cs_main);
	cout << "Thread_EventHandler is terminated !!\n";
	LeaveCriticalSection(&cs_main);
	GetExitCodeThread(hThrd_EventHandler, &nExitCode);
	CloseHandle(hThrd_EventHandler);


	cout << "Hit any key to terminate: ";
	_getch();
}
