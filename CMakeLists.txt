include_directories(.)

# cmake_minimum_required(VERSION <specify CMake version here>)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp PCB_table.cpp PCB_table.h PCB.cpp PCB.h random.h random.cpp scheduler.h scheduler.cpp)