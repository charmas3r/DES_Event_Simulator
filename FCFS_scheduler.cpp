#include "FCFS_scheduler.h"

//FCFS uses a standard queue for as the ready queue for pcbs
void FCFSScheduler::add_to_ready_queue(PCB* pcb)
{
  ready_queue.push(pcb);
}

//Pop from standard ready queue
PCB* FCFSScheduler::pop_ready_queue()
{
  if (ready_queue.size() != 0) {
    PCB *pcb = ready_queue.front();
    ready_queue.pop();
    return pcb;
  }
    return nullptr;
}
