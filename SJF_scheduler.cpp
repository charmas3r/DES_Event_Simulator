#include "SJF_scheduler.h"

//SJF uses a priority queue
void SJFScheduler::add_to_ready_queue(PCB* pcb)
{
  priority_queue.push(pcb);
}

//SJF uses a priority queue
PCB* SJFScheduler::pop_ready_queue()
{
  if (priority_queue.size() != 0) {
    PCB *pcb = priority_queue.top();
    priority_queue.pop();
    return pcb;
  }
  return nullptr;

}
