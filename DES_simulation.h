//
// Created by Evan Smith on 10/24/2019.
//

#ifndef UNTITLED_DES_SIMULATION_H
#define UNTITLED_DES_SIMULATION_H


class DES_simulation {
public:
    int currentTime;
    int arrivalTime;
    int turnaroundTime;
    int CPUTime;
    int IOTime;
    int ReadyQueueWaitingTime;

    DES_simulation();
    void FCFS_simulation();
    void SJF_simulation();
};


#endif //UNTITLED_DES_SIMULATION_H
