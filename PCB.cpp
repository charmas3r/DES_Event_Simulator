#include "PCB.h"
#include "random.h"

using namespace std;

//This is the default constructor for a PCB
PCB::PCB()
{
  processID = 0;
  priority = 0;
  processState = READY;
  //CPU duration can be between 1 sec and 1 min
  totalCPUDuration = RandomNumGen().ranInt(1000, 60000);
  remainingCPUDuration = 0;
  //Avg burst length can be between 5ms and 100ms.
  averageCPUBurstLength = RandomNumGen().ranInt(5, 100);
  nextCPUBurstLength = 0;
  //IO Burst times randomly determined between 30 to 100
  IOBurstTime = RandomNumGen().ranInt(30, 100);
  //start time can be between 1ms and 5 mins
  startTime = RandomNumGen().ranInt(1, 300000);
}

//one-arg constructor 
//@param id of process
PCB::PCB(int _processID) 
{
  processID = _processID;
  priority = 0;
  processState = READY;
  totalCPUDuration = RandomNumGen().ranInt(1000, 60000);
  remainingCPUDuration = 0;
  averageCPUBurstLength = RandomNumGen().ranInt(5, 100);
  nextCPUBurstLength = 0;
  IOBurstTime = RandomNumGen().ranInt(30, 100);
  startTime = RandomNumGen().ranInt(1, 300000);
}

//constructor for PCB Table
//@param _processID passed process id for PCB
//@param _state passed state for PCB
//@param _priority passed priority for PCB
PCB::PCB(int _processID, State _state, int _priority) {
  processID = _processID;
  priority = _priority;
  processState = _state;
  totalCPUDuration = RandomNumGen().ranInt(100, 60000);
  remainingCPUDuration = 0;
  averageCPUBurstLength = RandomNumGen().ranInt(5, 100);
  nextCPUBurstLength = 0;
  IOBurstTime = RandomNumGen().ranInt(30, 100);
  startTime = RandomNumGen().ranInt(1, 300000);
}
