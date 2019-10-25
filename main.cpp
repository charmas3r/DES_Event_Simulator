// Remember to add comments to your code

#include <iostream>
#include <cstdlib>
#include "event.h"
#include "SJF_scheduler.h"
#include "FCFS_scheduler.h"

int main(int argc, char* argv[]) {

    //Print basic information about the program
    std::cout << "=================================================================" << std::endl;
    std::cout << "CS 433 Programming assignment 3" << std::endl;
    std::cout << "Author: Evan Smith and Andrew Tse" << std::endl;
    std::cout << "Date: 10/23/2019" << std::endl;
    std::cout << "Course: CS433 (Operating Systems)" << std::endl;
    std::cout << "Description : Program to simulate CPU scheduling algorithms" << std::endl;
    std::cout << "=================================================================\n" << std::endl;

    int nproc = 1;		// number of processes to be simulated
    int scheduler_type = 1;


    //needed for program to be run via command line
    // TODO : Uncomment this when completed...
//    if(argc < 3 )
//    {
//        std::cerr << "Must specify the number of processes for simulation and type of scheduler" << std::endl;
//        std::cerr << "Usage: " << argv[0] << " <np> <scheduler type>" << std::endl;
//        std::cerr << "scheduler type 1: FCFS, 2: SJF" << std::endl;
//        exit(1);
//    } else
//    {
//        nproc = atoi(argv[1]);
//        scheduler_type = atoi(argv[2]);
//        if(nproc < 1)  // Do some error checking
//        {
//            while (nproc < 1) {
//                std::cerr << "Error: Must start with at least 1 process. Try again." << std::endl << std::endl;
//                std::cerr<< "How many initial processes to start simulation?"<< std::endl << std::endl;
//                std::cerr << "Enter selection: " << std::endl;
//                std::cin.clear();
//                std::cin >> nproc;
//                std::cerr << std::endl;
//            }
//        }
//        if(scheduler_type < 1 || scheduler_type > 2)
//        {
//            while (scheduler_type < 1 || scheduler_type > 2) {
//                std::cerr << "Error: Must choose from 2 given types. Try again." << std::endl << std::endl;
//                std::cerr << "Which scheduling algorithm would you like to use? " << std::endl;
//                std::cerr << "1) First Come First Serve" << std::endl;
//                std::cerr << "2) Shortest Job First" << std::endl << std::endl;
//                std::cerr << "Enter selection: ";
//                std::cin.clear();
//                std::cin >> scheduler_type;
//                std::cerr << std::endl;
//            }
//        }
//    }


    // Temporary prompt for testing
    // Gather args from user
    // TODO : comment this when completed...
    std::cout << "How many initial processes to start simulation?"<< std::endl << std::endl;
    std::cout << "Enter selection: " << std::endl;
    std::cin >> nproc;
    std::cout << std::endl;

    //Error handling for initial process amount
    while (nproc < 1) {
        std::cerr << "Error: Must start with at least 1 process. Try again." << std::endl << std::endl;
        std::cerr<< "How many initial processes to start simulation?"<< std::endl << std::endl;
        std::cerr << "Enter selection: " << std::endl;
        std::cin.clear();
        std::cin >> nproc;
        std::cerr << std::endl;
    }

    std::cout << "Which scheduling algorithm would you like to use? " << std::endl;
    std::cout << "1) First Come First Serve" << std::endl;
    std::cout << "2) Shortest Job First" << std::endl << std::endl;
    std::cout << "Enter selection: ";
    std::cin >> scheduler_type;
    std::cout << std::endl;

    while (scheduler_type < 1 || scheduler_type > 2) {
        std::cerr << "Error: Must choose from 2 given types. Try again." << std::endl << std::endl;
        std::cerr << "Which scheduling algorithm would you like to use? " << std::endl;
        std::cerr << "1) First Come First Serve" << std::endl;
        std::cerr << "2) Shortest Job First" << std::endl << std::endl;
        std::cerr << "Enter selection: ";
        std::cin.clear();
        std::cin >> scheduler_type;
        std::cerr << std::endl;
    }

    // Create a event queue
    EventQueue event_que;
    const int QUIT_TIME = 300000;	// 300,000 ms = 5 minutes

    Scheduler *p_scheduler;
    if(scheduler_type == 1) {
        std::cout << "****************Simulate FCFS scheduler****************************" << std::endl;
		p_scheduler = new FCFSScheduler(nproc, &event_que);
		//start simulation

		//The general algorithm of a DES is a while loop which continues as long as there are events remaining in the
        //event queue to be processed.
		while (!event_que.empty()) {

		}

    } else if (scheduler_type == 2)
    {
        std::cout << "****************Simulate SJF scheduler****************************" << std::endl;
		p_scheduler = new SJFScheduler(nproc, &event_que);
    }
    // TODO: Make sure to add Process_Arrival events of all processes to the event queue

    int current_time = 0;
    // Main loop of the simulation
    while(!event_que.empty() && current_time < QUIT_TIME) {
        Event e = event_que.top();		// get the next event
        event_que.pop();					// remove the next event from queue
        // Handle the event
        p_scheduler->handle_the_event(e);
    }

    delete p_scheduler;
}
