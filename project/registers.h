//
// Created by michal on 10.09.17.
//

#ifndef PROJECT_REGISTERS_H
#define PROJECT_REGISTERS_H

#include <stdint.h>
#include <vector>

struct VMRegister {
    int64_t value;
};

std::vector<VMRegister> vm_register(16);

#endif //PROJECT_REGISTERS_H
