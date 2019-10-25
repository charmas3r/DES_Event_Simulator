#include <iostream>
#include "scheduler.h"
#include "event.h"


// Constructor creates nproc number of processes with random distribution as described
// in the assignment. The processes are stored in a PCB table.
Scheduler::Scheduler(int nproc, EventQueue* p_event_queue)
{
	// The queue must be populated with at least one initial event before the while loop
	// commences.
	p_EQ = p_event_queue;
	//initializing event with process id = 0 and current time = 0.
	Event *event = new Event(0, Process_Arrival, 0);
	p_EQ->push(*event);

	std::clog << "Scheduler: Size of event queue is now:"+ std::to_string(p_EQ->size()) << std::endl;

	//random distributions implemented in PCB class
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
	// TODO: Add your implementation here
}

/**
 * \brief 
 * \param e 
 */
void Scheduler::handle_proc_arrival(const Event& e)
{
	// TODO: Add your implementation here
}

/**
 * \brief 
 * \param e 
 */
void Scheduler::handle_cpu_completion(const Event& e)
{
	// TODO: Add your implementation here

}

/**
 * \brief 
 * \param e 
 */
void Scheduler::handle_io_completion(const Event& e)
{
	//TODO: Add your implementation here
}

/**
 * \brief 
 * \param e 
 */
void Scheduler::handle_timer_expiration(const Event& e)
{
	// Add your implementation here
}
