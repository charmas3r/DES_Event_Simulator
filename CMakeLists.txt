include_directories(.)

# cmake_minimum_required(VERSION <specify CMake version here>)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        assign3
        main.cpp
        PCB_table.cpp
        PCB_table.h
        PCB.cpp
        PCB.h
        random.h
        random.cpp
        scheduler.h
        scheduler.cpp
        FCFS_scheduler.cpp
        FCFS_scheduler.h
        SJF_scheduler.cpp
        SJF_scheduler.h)