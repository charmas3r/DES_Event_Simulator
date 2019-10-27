#include <iostream>
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

	for (int i = 0; i < nproc; i++) {
		PCB pcb(i);
		procs.process_list.push_back(pcb);

		Event *event = new Event(i, Process_Arrival, pcb.startTime);
		p_EQ->push(*event);
	}

	// Initialize the CPU and start idling. No process dispatched yet.
	currentCPU.CPU_STATE = IDLE;

	std::clog << "Scheduler: Size of event queue is now: "+ std::to_string(p_EQ->size()) << std::endl;
}

/**
 * \brief 
 * \param e 
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
	std::clog << "Scheduler: Processing scheduling (dispatch) initiated. " << std::endl;
	//first check if CPU is idle and the queue isn't empty
	if (currentCPU.CPU_STATE == IDLE && !ready_queue.empty()) {
		PCB *pcb = ready_queue.front();
		ready_queue.pop();
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
void Scheduler::handle_proc_arrival(const Event& e)
{
	//TODO : need to add stats
	std::clog << "Scheduler: Process arrival handling started." << std::endl;
	PCB *arrivalPCB = &procs.process_list[e.procID];
	//generating the next CPU burst based on the average
	arrivalPCB->nextCPUBurstLength = RandomNumGen().CPUBurstRandom(arrivalPCB->averageCPUBurstLength);
	arrivalPCB->processState = READY;
	//add to ready queue
	ready_queue.push(arrivalPCB);
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
	//TODO : need to add stats
	std::clog << "Scheduler: Cpu completion handling started." << std::endl;
	PCB *completedPCB = &procs.process_list[e.procID];
	completedPCB->remainingCPUDuration -= completedPCB->nextCPUBurstLength;

	if(completedPCB->remainingCPUDuration <= 0) {
	    std::clog << "PCB id:" << completedPCB->processID << " completed." << std::endl;
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
 * \brief I/O Completion event represents that a process has completed its I/O burst. A new CPU burst time is
randomly determined, and then this process is moved to the ready queue. If the CPU is now idle, then a
process from the ready queue can be selected and dispatched.
 * \param e 
 */
void Scheduler::handle_io_completion(const Event& e)
{
	//TODO : need to add stats
	std::clog << "Scheduler: IO completion handling started." << std::endl;
	PCB *IOCompletedPCB = &procs.process_list[e.procID];
	// Assign new CPU burst time
	IOCompletedPCB->nextCPUBurstLength = RandomNumGen().CPUBurstRandom(IOCompletedPCB->averageCPUBurstLength);
	IOCompletedPCB->processState = READY;
	ready_queue.push(IOCompletedPCB);
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
	std::clog << "Scheduler: Timer expiration handling started." << std::endl;
	PCB *expiredPCB = &procs.process_list[e.procID];
	expiredPCB->processState = READY;
	expiredPCB->nextCPUBurstLength = RandomNumGen().CPUBurstRandom(expiredPCB->averageCPUBurstLength);
	ready_queue.push(expiredPCB);
	currentCPU.CPU_STATE = IDLE;
	schedule();
}
