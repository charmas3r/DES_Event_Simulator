#include <iostream>
#include "scheduler.h"
#include "event.h"


// Constructor creates nproc number of processes with random distribution as described
// in the assignment. The processes are stored in a PCB table.
Scheduler::Scheduler(int nproc, EventQueue* p_event_queue)
{
	// The queue must be populated with at least one initial event before the while loop
	// commences. Add process arrival event for each process
	p_EQ = p_event_queue;

	//need to change start time for event to be random start time for process..
	for (int i = 0; i < nproc; i++) {
		Event *event = new Event(i, Process_Arrival, i);
		p_EQ->push(*event);
	}

	std::clog << "Scheduler: Size of event queue is now: "+ std::to_string(p_EQ->size()) << std::endl;

	//random distributions implemented in PCB class
	//we'll need to change this to enter each process to the table in the for-loop so we can capture the
	//random start time and assign it properly to event queue
	procs.createPCBTable(nproc);
}

/**
 * \brief 
 * \param e 
 */
void Scheduler::handle_the_event(const Event& e)
{
	// Call different handling function according to the event type
	switch (e.type)
	{
	case Process_Arrival:
		handle_proc_arrival(e);
		break;
	case CPU_Burst_Completion:
		handle_cpu_completion(e);
		break;
	case IO_Burst_Completion:
		handle_io_completion(e);
		break;
	case Timer_Expiration:
		handle_timer_expiration(e);
		break;
	}
}

void Scheduler::schedule()
{
	std::clog << "Scheduler: Processing scheduling (dispatch) initiated. " << std::endl;
}

/**
 * \brief 
 * \param e 
 */
void Scheduler::handle_proc_arrival(const Event& e)
{
	std::clog << "Scheduler: Process arrival handling started." << std::endl;


}

/**
 * \brief 
 * \param e 
 */
void Scheduler::handle_cpu_completion(const Event& e)
{
	std::clog << "Scheduler: Cpu completion handling started." << std::endl;

}

/**
 * \brief 
 * \param e 
 */
void Scheduler::handle_io_completion(const Event& e)
{
	std::clog << "Scheduler: IO completion handling started." << std::endl;
}

/**
 * \brief 
 * \param e 
 */
void Scheduler::handle_timer_expiration(const Event& e)
{
	std::clog << "Scheduler: Timer expiration handling started." << std::endl;
}
