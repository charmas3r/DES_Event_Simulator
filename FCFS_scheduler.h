#pragma once
#include <iostream>
#include "scheduler.h"

class FCFSScheduler : public Scheduler
{
public:
	/**
	 * \brief First Come First Served (SJF) Scheduler Constructor
	 * \param nproc nproc Number of processes simulated
	 * \param p_event_queue p_event_queue Pointer to the Event queue of simulation
	 */
	FCFSScheduler(int nproc, EventQueue* p_event_queue)
		: Scheduler(nproc, p_event_queue)
	{
//		procs.createPCBTable(nproc);
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
