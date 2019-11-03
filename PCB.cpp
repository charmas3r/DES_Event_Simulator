#include "PCB.h"
#include "random.h"

using namespace std;

//one-arg constructor 
//@param id of process
PCB::PCB(int _processID) 
{
  processID = _processID;
  priority = 0;
  processState = READY;
  totalCPUDuration = 0;
  remainingCPUDuration = 0;
  averageCPUBurstLength = 0;
  nextCPUBurstLength = 0;
  IOBurstTime = 0;
  arrivalTime = 0;
  startTime = 0;
  turnaroundTime = 0;
  totalIOTime = 0;
  readyQueueWaitingTime = 0;
}
