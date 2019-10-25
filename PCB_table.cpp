//
// Created by User on 10/24/2019.
//

#include "PCB_table.h"
#include "PCB.h"

PCB_table::PCB_table() {
    //not sure what to put in here...
}

void PCB_table::createPCBTable(int size) {
    for (int i = 0; i < size; i++) {
        PCB spawnedPCB(i, READY, i);
        process_list.emplace_back(spawnedPCB);
    }
}