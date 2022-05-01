#ifndef EVENT_H
#define EVENT_H
#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum EventStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED };

#define MAX_EVENT_PRIORRITY 100
#define NUM_EVENT_GENERATOR 10

class Event
{
	friend ostream& operator<<(ostream& fout, const Event& e);
public:
	Event() {}
	Event(int evt_no, int evt_pri, int genAddr);
	~Event() {}
	void printEvent(ostream& fout);
	void printEvent_Proc(ostream& fout);
	void setEventNo(int evtNo) { event_no = evtNo; }
	void setEventGenAddr(int evtGenAddr) { event_gen_addr = evtGenAddr; }
	void setEventHandlerAddr(int evtHndlerAddr) { event_handler_adrr = evtHndlerAddr; }
	void setEventPriority(int evtPrior) { event_pri = evtPrior; }
	void setEventStatus(EventStatus evtStatus) { eventStatus = evtStatus; }
	void setEventElapsedTime(double t_elapsed_ms) { t_elapsed_time_ms = t_elapsed_ms; }
	void setEventGenTime(LARGE_INTEGER t_gen) { t_event_gen = t_gen; }
	void setEventProcTime(LARGE_INTEGER t_proc) { t_event_proc = t_proc; }
	int getEventPri() { return event_pri; }
	int getEventNo() { return event_no; }
	double getEventElapsedTime() { return t_elapsed_time_ms; }
	LARGE_INTEGER getEventGenTime() { return t_event_gen; }
	LARGE_INTEGER getEventProcTime() { return t_event_proc; }
	bool operator>(Event& e) { return event_pri > e.event_pri; }
	bool operator<(Event& e) { return event_pri < e.event_pri; }
private:
	int event_no;
	int event_gen_addr;
	int event_handler_adrr;
	int event_pri;
	LARGE_INTEGER t_event_gen;
	LARGE_INTEGER t_event_proc;
	double t_elapsed_time_ms;
	EventStatus eventStatus;
};

Event* genRandEvent(int evt_no);
unsigned __stdcall Thread_EventGenerator(LPVOID pParam);
unsigned __stdcall Thread_EventHandler(LPVOID pParam);
#endif // !EVENT_H
