#include "Event.h"

Event::Event(int evt_no, int evt_pri, int genAddr)
{
	this->event_no = evt_no;
	this->event_pri = evt_pri;
	this->event_gen_addr = genAddr;
	this->event_handler_adrr = -1;
	this->eventStatus = GENERATED;
}

Event* genRandEvent(int evt_no)
{
	Event* pEv;
	int evt_prio;
	int evt_generator_id;
	evt_prio = rand() % MAX_EVENT_PRIORRITY;
	evt_generator_id = rand() & NUM_EVENT_GENERATOR;

	pEv = new Event(evt_no, evt_prio, evt_generator_id);
	return pEv;
}

void Event::printEvent(ostream& fout)
{
	fout << "Ev(pri:" << setw(3) << event_pri << ", gen: " << setw(3) << event_pri;
	fout << ", no:" << setw(3) << event_no << ") ";


}

void Event::printEvent_Proc(ostream& fout)
{
	fout << "Ev(no: " << setw(2) << event_no << ", pri: " << setw(2) << event_pri;
	fout.precision(2);
	fout.setf(ios::fixed);
	fout << ", t_elapsed: " << setw(8) << t_elapsed_time_ms << ") ";
}

ostream& operator<<(ostream& fout, const Event& evt)
{
	fout << "Ev(no:" << setw(3) << evt.event_no;
	fout << ", pri:" << setw(3) << evt.event_pri << ") ";

	return fout;
}