#pragma once
#include "scheduler.h"
#include <vector>
#include <queue>
#include "PCB.h"

// Remember to add comments to your code
//
class ReadyQueueCompare {
 public:
  bool operator()(const PCB& p1, const PCB& p2){
    return (p1.totalCPUDuration > p2.totalCPUDuration);
  }
};

class SJFScheduler : public Scheduler
{
public:
  std::priority_queue<PCB*, std::vector<PCB*>, ReadyQueueCompare> priority_queue;
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
