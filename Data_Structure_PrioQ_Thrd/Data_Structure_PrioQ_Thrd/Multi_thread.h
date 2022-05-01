#ifndef MULTI_THREAD_H
#define MULTI_THREAD_H
#include "Event.h"
#include "HeapPrioQ.h"
#include "SimParams.h"
#include <thread>
enum ROLE { EVENT_GENERATOR, EVENT_HANDLER };
enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE };

typedef struct ThreadStatusMonitor
{
	int numEventGenerated;
	int numEventProcessed;
	int totalEventGenerated;
	int totalEventProcessed;
	Event eventGenerated[TOTAL_NUM_EVENTS];
	Event eventProcessed[TOTAL_NUM_EVENTS];
	THREAD_FLAG* pFlagThreadTerminate;
}ThreadStatusMonitor;

typedef struct ThreadParam
{
	CRITICAL_SECTION* pCS_main;
	CRITICAL_SECTION* pCS_thrd_mon;
	HeapPrioQueue<int, Event>* pPriQ_Event;
	ROLE role;
	int myAddr;
	int maxRound;
	int targetEventGen;
	ThreadStatusMonitor* pThrdMon;
	LARGE_INTEGER QP_freq;
}ThreadParam_Event;


#endif // ! MULTI_THREAD_H
