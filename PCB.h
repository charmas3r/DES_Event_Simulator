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
  
  //times
  int totalCPUDuration;
  int remainingCPUDuration;
  int averageCPUBurstLength;
  int nextCPUBurstLength;
  int IOBurstTime;
  int startTime;

  //constructors
  PCB();
  PCB(int _processID);
  PCB(int _processID, State _state, int _priority);
};

