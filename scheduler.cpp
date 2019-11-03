#include <iostream>
#include <iomanip>
#include "scheduler.h"
#include "event.h"
#include "random.h"


// Constructor creates nproc number of processes with random distribution as described
// in the assignment. The processes are stored in a PCB table.
Scheduler::Scheduler(int nproc, EventQueue* p_event_queue)
{
	// The queue must be populated with at least one initial event before the while loop
	// commences. Add process arrival event for each process. Random distributions implemented in PCB class

	p_EQ = p_event_queue;

	//keeps track of last pcb's finish time and process load
	currentCPU.previousFinish = 0;
	currentCPU.processLoad = nproc;

	long seed = -2;
	RandomNumGen rg(seed);

	for (int i = 0; i < nproc; i++) {
		PCB pcb(i);
		pcb.arrivalTime = rg.ranInt(1, 300000);
		pcb.IOBurstTime = rg.ranInt(30, 100);
		pcb.averageCPUBurstLength = rg.ranInt(5, 100);
		pcb.totalCPUDuration = rg.ranInt(1000, 60000);
		pcb.remainingCPUDuration = pcb.totalCPUDuration;
		procs.process_list.push_back(pcb);

		Event *event = new Event(i, Process_Arrival, pcb.arrivalTime);
		p_EQ->push(*event);
	}

	// Initialize the CPU and start idling. No process dispatched yet.
	currentCPU.CPU_STATE = IDLE;
}

/**
 * \brief Handles the event upon arrival from main.cpp
 * \param e Event being handled
 */
void Scheduler::handle_the_event(const Event& e)
{
	// Call different handling function according to the event type
	switch (e.type)
	{
		case Process_Arrival:
			handle_proc_arrival(e);
			break;
		case CPU_Burst_Completion:
			handle_cpu_completion(e);
			break;
		case IO_Burst_Completion:
			handle_io_completion(e);
			break;
		case Timer_Expiration:
			handle_timer_expiration(e);
			break;
	}
}

/**
 * \brief The simulation checks to see if the CPU is idle. If it is, then a process can be selected
 * from the ready queue and dispatched. Dispatching a process involves assigning that process to the
 * CPU, creating an event for the time when its CPU burst will complete, and adding that event to the
 * event queue
 * \param e Arrival event to be processed
 */
void Scheduler::schedule()
{
	//first check if CPU is idle and the queue isn't empty
	PCB *pcb = pop_ready_queue();
	if (currentCPU.CPU_STATE == IDLE && pcb != nullptr) {
		//dispatch to CPU
		currentCPU.CPU_JOB = pcb;
		//set the CPU state to BUSY
		currentCPU.CPU_STATE = BUSY;
		//set process state also
		pcb->processState = RUNNING;

		//next we need to create the event for the time when the CPU burst will complete and add to
		//event queue ...
		Event *futureEvent = new Event(pcb->processID, CPU_Burst_Completion, pcb->nextCPUBurstLength);
		p_EQ->push(*futureEvent);
	}


}

/**
 * \brief When this event is handled, the process is added to the ready queue (a separate queue, don’t
 * confuse it with the event queue)
 * \param e Arrival event to be processed
 */
void Scheduler::handle_proc_arrival(const Event& e) {
	PCB *arrivalPCB = &procs.process_list[e.procID];
	//generating the next CPU burst based on the average
	arrivalPCB->nextCPUBurstLength = RandomNumGen().CPUBurstRandom(arrivalPCB->averageCPUBurstLength);
	arrivalPCB->processState = READY;
	//add to ready queue
	add_to_ready_queue(arrivalPCB);
	//see if it's waiting
	if(arrivalPCB->arrivalTime < currentCPU.previousFinish) {
		//record for how long it has to wait.
		arrivalPCB->readyQueueWaitingTime = currentCPU.previousFinish - arrivalPCB->arrivalTime;
		//change start time to reflect real start time.
		arrivalPCB->startTime = arrivalPCB->arrivalTime + arrivalPCB->readyQueueWaitingTime;
	} else {
		arrivalPCB->startTime = arrivalPCB->arrivalTime;
	}
	//send to dispatch
	schedule();
}

/**
 * \brief CPU Burst Completion event represents that a process has completed its current CPU burst in the CPU.
If this process has not yet completed its total execution time, then a random I/O time is determined for
this process’s next I/O burst. We assume an infinite number of I/O devices, so a process can be
immediately assigned to an I/O device without waiting. An I/O completion event generated for the
time when the I/O burst will complete is added to the event queue. Alternatively, if this process has
completed its total CPU time, then it can be removed from the system. In either case, the ready queue
is checked, and if it is not empty, then a new process is selected and dispatched.
 * \param e 
 */
void Scheduler::handle_cpu_completion(const Event& e)
{
	PCB *completedPCB = &procs.process_list[e.procID];
	completedPCB->remainingCPUDuration -= completedPCB->nextCPUBurstLength;

	if(completedPCB->remainingCPUDuration <= 0) {

		//get finish time
		int finishTime  = completedPCB->startTime +
						  completedPCB->totalIOTime +
						  completedPCB->totalCPUDuration;


		if (finishTime < currentCPU.totalCPUOnTime) {
			//get turnaround time
			int turnaroundTime = completedPCB->totalIOTime +
								 completedPCB->totalCPUDuration +
								 completedPCB->readyQueueWaitingTime;


			//add to cpu var stats
			currentCPU.totalWaitTime += completedPCB->readyQueueWaitingTime;
			currentCPU.totalTurnaroundTime += turnaroundTime;
			currentCPU.totalUtilizedTime += (completedPCB->totalCPUDuration + completedPCB->totalIOTime);

			//add process load counter
			currentCPU.processCounter++;

			//print stats once completed
			std::cout << "Process: " << completedPCB->processID << std::endl;
			std::cout << "Arrival time: " <<completedPCB->arrivalTime << " ms" << std::endl;
			std::cout << "Start time: " << completedPCB->startTime << " ms"  << std::endl;
			std::cout << "Finish time: " << finishTime << " ms"  << std::endl;
			std::cout << "Turnaround time: " << turnaroundTime << " ms" << std::endl;
			std::cout << "CPU time: " << completedPCB->totalCPUDuration << " ms" << std::endl;
			std::cout << "IO time: " << completedPCB->totalIOTime << " ms" << std::endl;
			std::cout << "Ready Queue Waiting Time: " << completedPCB->readyQueueWaitingTime << " ms"
					  << std::endl << std::endl << std::endl;

			currentCPU.previousFinish = finishTime;

		}
		//remove event from system
		completedPCB->processState = TERMINATED;
	} else {
		// IO event initiation
		completedPCB->IOBurstTime = RandomNumGen().ranInt(30, 100);
		// IO completion event generation
		Event *IOCompletetionEvent = new Event(e.procID, IO_Burst_Completion, completedPCB->IOBurstTime);
		p_EQ->push(*IOCompletetionEvent);
	}
	currentCPU.CPU_STATE = IDLE;
	schedule();
}


/**
 * \brief Function called from main.cpp after total cpu time is up to. It's purpose is to print system statistics.
 */
void Scheduler::print_cpu_stats()
{

	//get utilization rate and throughput
	double utilizationRate = ((double)currentCPU.totalUtilizedTime / (double)currentCPU.totalCPUOnTime) * 100;
	double throughput = ((double)currentCPU.processCounter / (double)currentCPU.totalCPUOnTime) * 1000;

	std::cout << "============================================================" << std::endl;
	std::cout << "CPU Utilization: " << utilizationRate <<"%" << std::endl;
	std::cout << "Throughput: " << std::fixed << std::setprecision(4) << throughput << " jobs/s" << std::endl;
	std::cout << "Average turnaround time: " << currentCPU.totalTurnaroundTime / currentCPU.processCounter << " ms" << std::endl;
	std::cout << "Average waiting time: " << currentCPU.totalWaitTime / currentCPU.processCounter << " ms" << std::endl << std::endl;

}

/**
 * \brief I/O Completion event represents that a process has completed its I/O burst. A new CPU burst time is
randomly determined, and then this process is moved to the ready queue. If the CPU is now idle, then a
process from the ready queue can be selected and dispatched.
 * \param e 
 */
void Scheduler::handle_io_completion(const Event& e)
{
	PCB *IOCompletedPCB = &procs.process_list[e.procID];
	// Save IO time to total IO duration
	IOCompletedPCB->totalIOTime += IOCompletedPCB->IOBurstTime;
	// Assign new CPU burst time
	IOCompletedPCB->nextCPUBurstLength = RandomNumGen().CPUBurstRandom(IOCompletedPCB->averageCPUBurstLength);
	IOCompletedPCB->processState = READY;
	add_to_ready_queue(IOCompletedPCB);
	schedule();
}

/**
 * \brief  If the timer expires before the process’ CPU burst completes, then the timer
expiration event triggers a context switch, moving that process from the CPU to the ready queue and
selecting a new process from the ready queue to run next. If the process finishes its CPU burst before
the timer expires, then the timer expiration event is a null event, and can just be discarded when it exits
the event queue.
 * \param e 
 */
void Scheduler::handle_timer_expiration(const Event& e)
{
	PCB *expiredPCB = &procs.process_list[e.procID];
	expiredPCB->processState = READY;
	expiredPCB->nextCPUBurstLength = RandomNumGen().CPUBurstRandom(expiredPCB->averageCPUBurstLength);
	add_to_ready_queue(expiredPCB);
	currentCPU.CPU_STATE = IDLE;
	schedule();
}
