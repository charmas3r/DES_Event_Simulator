//
// Created by User on 10/24/2019.
//

#ifndef UNTITLED_PCB_TABLE_H
#define UNTITLED_PCB_TABLE_H

#include <vector>
#include "PCB.h"

class PCB_table {
public:
    std::vector<PCB> process_list;
    PCB_table();
    void createPCBTable(int size);
private:

};


#endif //UNTITLED_PCB_TABLE_H
