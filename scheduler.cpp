#include "scheduler.h"

// Add your implementations here

Scheduler::Scheduler(int nproc, EventQueue* p_event_queue)
{
	p_EQ = p_event_queue;

	// TODO: Add implementation to create nproc processes with random distribution as described in the assignment
	// TODO: Those processes should be stored in the PCBTable
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
	case Event::Process_Arrival:
		handle_proc_arrival(e);
		break;
	case Event::CPU_Burst_Completion:
		handle_cpu_completion(e);
		break;
	case Event::IO_Burst_Completion:
		handle_io_completion(e);
		break;
	case Event::Timer_Expiration:
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
