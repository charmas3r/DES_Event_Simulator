#pragma once
#include "event.h"
#include "PCB.h"
#include "PCB_table.h"

// Base Scheduler Class
class Scheduler {
public:
    /**
     * \brief Constructor
     * \param nproc Number of processes simulated
     * \param p_event_queue Pointer to the Event queue of simulation
     */
    Scheduler(int nproc, EventQueue* p_event_queue);

    // Destructor
    virtual ~Scheduler() {};

    /**
     * \brief Event handling function. It calls actual handling function according to the event type
     * \param e 
     */
    void handle_the_event(const Event& e);


    /**
	 * \brief Check if the scheduler should dispatch a ready process to run
	 * A pure virtual function to be overridden in the subclass of specific scheduler. 
	 */
	virtual void schedule();


    /**
	 * \brief Add a process to ready queue
	 * \param pcb
	 * A pure virtual function to be overridden in the subclass of specific scheduler. 
	 */
	virtual void add_to_ready_queue(PCB* pcb) = 0;

	/**
	 * \brief Remove next process from ready queue according to the scheduling algorithm
	 * A pure virtual function to be overridden in the subclass of specific scheduler. 
	 */
	virtual PCB* pop_ready_queue() = 0;

protected:

    /**
     * \brief Event handling function for process arrival event
     * \param e 
     */
    void handle_proc_arrival(const Event& e);

    /**
     * \brief Event handling function for CPU burst completion event
     * \param e 
     */
    void handle_cpu_completion(const Event& e);

    /**
	 * \brief 
	 * \param e 
	 */
	void handle_io_completion(const Event& e);

    /**
     * \brief 
     * \param e 
     */
	void handle_timer_expiration(const Event& e);

	// Table of all processes 
	PCB_table procs;

	// Pointer to the event queue
	EventQueue* p_EQ;
};

