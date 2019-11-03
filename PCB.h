#pragma once

//State should be an enum
enum State {
	READY,
	RUNNING,
	WAITING,
	TERMINATED 
};

class PCB {
public:
  int processID;
  int priority;
  State processState;
  long seed;
  
  //times
  int totalCPUDuration;
  int remainingCPUDuration;
  int averageCPUBurstLength;
  int nextCPUBurstLength;
  int IOBurstTime;
  int arrivalTime;
  int startTime;
  int turnaroundTime;
  int totalIOTime;
  int readyQueueWaitingTime;

  //constructors
  PCB(int _processID);
  PCB(int _processID, State _state, int _priority);
};

