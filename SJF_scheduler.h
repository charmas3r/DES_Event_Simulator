#pragma once
#include "scheduler.h"

// Remember to add comments to your code
//
class SJFScheduler : public Scheduler
{
public:
	/**
	 * \brief Shortest Job First (SJF) Scheduler Constructor
	 * \param nproc nproc Number of processes simulated
	 * \param p_event_queue p_event_queue Pointer to the Event queue of simulation
	 */
	SJFScheduler(int nproc, EventQueue* p_event_queue)
		: Scheduler(nproc, p_event_queue)
	{

	}

	
	/**
	 * \brief 
	 * \param pcb 
	 */
	virtual void add_to_ready_queue(PCB* pcb) override;

	/**
	 * \brief
	 */
	virtual PCB* pop_ready_queue() override;
};