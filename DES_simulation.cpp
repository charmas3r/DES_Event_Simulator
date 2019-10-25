//
// Created by Evan Smith on 10/24/2019.
//

#include "DES_simulation.h"

//default constructor for simulation
DES_simulation::DES_simulation() {
    currentTime = 0;
    arrivalTime = 0;
    turnaroundTime = 0;
    CPUTime = 0;
    IOTime = 0;
    ReadyQueueWaitingTime = 0;
}

//Initializes the event queue
void DES_simulation::init() {
    // The queue must be populated with at least one initial event before the while loop
    // commences.  In this case, the event queue will be populated with a number of “Process Arrival” events for all
    //simulated processes. The number of processes is specified by parameter on the command line.
}

//First Come First Serve simulation
//This function will simulate the FCFS algorithm by looping through the event queue
//and using the Scheduler class to handle the event. Once finished a report is generated
//with scheduling statistics
void DES_simulation::FCFS_simulation() {

    //The general algorithm of a DES is a while loop which continues as long as there are events remaining in the
    //event queue to be processed. The while loop
    //extracts the next event from the event queue, determines what type of event it is, and processes it accordingly,
    //for example, using a switch statement on the event type
}

//Shortest Job First simulation
//This function will simulate the SJF algorithm by looping through the event queue
//and using the Scheduler class to handle the event. Once finished a report is generated
//with scheduling statistics
void DES_simulation::SJF_simulation() {

}
